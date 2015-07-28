# -*- coding: utf-8 -*-
require "ruby-graphviz"
require 'digest/sha1'
require 'pp'
require 'fileutils'
require_relative 'yamlstate.rb'

 def comment(condition)
  if condition.nil? || condition.empty? 
    ""
  else
    "  //  #{condition}?"
  end
 end

 def export_graph(data, class_name, dst_dir)
  g = GraphViz::new(class_name)
  nodes = {}
  data.nodes.each do | node |
    shape = "ellipse"
    shape = "box" if node.rlink.empty? || node.link.empty?
    nodes[node.name] = g.add_nodes(node.name, :shape => shape)
  end

  data.nodes.each do | node |
    node.link.each do | link |
      if link.condition.nil?
        g.add_edges(nodes[link.from.name], nodes[link.to.name], :weight => "100")
      else
        weight = "1"
        weight = "0.01" if link.from.rlink.empty? || link.to.link.empty?
        g.add_edges(nodes[link.from.name], nodes[link.to.name], :weight => weight, :label => link.condition + "?", :style => "dotted")
      end
    end
  end

  g.output( :pdf => "#{dst_dir}/#{class_name}.pdf", :png => "#{dst_dir}/#{class_name}.png",:svg => "#{dst_dir}/#{class_name}.svg" )
end

def state2cpp(yaml_file)
  class_name = File.basename(yaml_file,".*")
  yaml_dir = File.dirname(yaml_file)

  conf_file = yaml_dir + "/" + class_name + ".conf"
  conf_file = yaml_dir + "/state2cpp.conf" unless File.exist?(conf_file)

  cpp_head = ""
  cpp_foot = ""
  h_template = ""
  dst_dir = "."

  if File.exist?(conf_file)
    data = YAML.load(File.read(conf_file))
    cpp_head = data["cpp_head"] || ""
    cpp_foot = data["cpp_foot"] || ""
    dst_dir = yaml_dir + "/" + data["dst_dir"] || "."
    h_template = data["h_template"] || ""
  end

  cpp_path = "#{dst_dir}/#{class_name}States.cpp"
  h_path = "#{dst_dir}/#{class_name}States.h"

  class_header_path = "#{dst_dir}/#{class_name}.h"
  unless File.exist?(class_header_path)
    File.open(class_header_path, "w:UTF-8") { | file |
      file.print <<END
#{h_template.gsub("_CLASS_NAME_", class_name)}
END
    }
  end

  data = YamlState.new
  data.add(yaml_file)
  export_graph(data, class_name, yaml_dir)
  root = []
  data.nodes.sort{|a,b| a.name <=> b.name }.each do | node |
    next unless node.rlink.empty?
    root << node
  end

  header = ""
  header +=<<END
// [state2cpp] please include this file ins the declaration of class #{class_name}.

private:
  StateMachine _stateMachine;
public:
  void StartState();
  void ExecState();
  std::string DumpState() const;

private:
END

  data.nodes.each do |n|
    header +=<<END
  void State#{n.name}();
END
  end
  File.open(h_path, "w:UTF-8") { | file |
    file.print header
  }

  sources = []
  source = ""
source +=<<END
#include "#{class_name}.h"
#{cpp_head}

#define TO_STRING() \\
  _stateMachine.to_string()
#define EXEC() \\
  _stateMachine.Exec()
#define SPAWN(state) \\
  _stateMachine.Spawn(std::make_pair([&]{state();}, #state))
#define SWITCH_TO(state) \\
  _stateMachine.SwitchTo(std::make_pair([&]{state();}, #state))
#define YIELD_TO(state) \\
  _stateMachine.YieldTo(std::make_pair([&]{state();}, #state))
#define EXIT() _stateMachine.Exit()

std::string #{class_name}::DumpState() const {
    return TO_STRING();
}

void #{class_name}::ExecState() {
    EXEC();
}

void #{class_name}::StartState() {
END

  root.each_with_index do | node, i |
    p = ""
    p = "//  " if i != 0
  source += <<END
    #{p}SPAWN(State#{node.name});
END
  end

  source += <<END
}
END

  sources << [nil, source]

  data.nodes.each do |n|
    source = ""
    source += <<END
void #{class_name}::State#{n.name}() {

    //  TODO: Something to execute every frame while this state.

END
    case n.link.length
    when 0
      source += <<END
    if (false) {
        EXIT();
    }
END
    when 1
      link = n.link[0]
      condition = link.condition
      if condition.nil?
        indent = ""
        source += <<END
END
      else
        indent = "    "
        source += <<END
    if (false) {#{comment(condition)}
END
      end

      source += <<END
    #{indent}SWITCH_TO(State#{link.to.name});
END

      if indent != ""
        source += <<END
    }
END
      end
    else
      count = 0
      n.link.sort{|a,b|
        if a.condition.nil? == b.condition.nil?
          a.to.name <=> b.to.name
        elsif a.condition.nil?
          1
        else
          -1
        end
      }.each do | link |
        if link.spawn
          source += <<END
    SPAWN(State#{link.to.name});
END
          source.puts
        end
      end

      n.link.sort{|a,b|
        if a.condition.nil? == b.condition.nil?
          a.to.name <=> b.to.name
        elsif a.condition.nil?
          1
        else
          -1
        end
      }.each do | link |
        next if link.spawn
        condition = link.condition
        if count == 0
          source += <<END
    if (false) { //  #{condition}
END
        elsif link.condition.nil? && count == n.link.size-1
          source += <<END
    } else {
END
        else
          source += <<END
    } else if (false) {#{comment(condition)}
END
        end
        count += 1
        source += <<END
        SWITCH_TO(State#{link.to.name});
END
      end
      source += <<END
    }
END
    end

    source += <<END
}
END
    sources << [n.name, source]
  end

  old_sources = {}
  old_disabled = ""

  if File.exist?(cpp_path)
    File.open(cpp_path, "r:UTF-8") { | file |
      source = ""
      hash = nil
      name = nil
      is_disabled = false
      while l = file.gets
        if l =~ /\/\/\s*\[state2cpp\]__disabled__/
          is_disabled = true
        elsif l =~ /\/\/\s*\[state2cpp\]([^:]+):(\w+)/
          is_disabled = false
          unless name.nil?
            old_sources[name] = [hash, source.strip()+"\n"]
          end
          name = $1
          hash = $2
          source = ""
        else
          if is_disabled
            old_disabled << l
          else
            source << l
          end
        end
      end
    }
  end

  source_names = []

  File.open(cpp_path, "w:UTF-8") { | file |
    sources.each do | name, source |
      if name.nil?
        file.print source
      else
        source_names << name
        nospace_source = source.gsub(/[   　\n]/, '')
        hash = Digest::SHA1.hexdigest(nospace_source)
        file.print "\n// [state2cpp]#{name}:#{hash}\n\n"
        if old_sources.has_key?name
          old_hash, old_source = old_sources[name]
          if hash == old_hash
            file.print old_source
          else
            file.print source
            file.print <<END
#if 0 // yaml file is modified. Please remove this chunk.
#{old_sources[name][1]}
#endif
END
          end
        else
          file.print source
        end
      end
    end
    old_sources.each do | name, a |
      next if source_names.include?name
      file.print <<END
#if 0 // deleted in the yaml file. Please remove this chunk.
#{a[1]}
#endif
#{old_disabled}
END
    end
    file.print(cpp_foot)
  }
end

if __FILE__ == $0
  ARGV.each do | yaml |
    state2cpp(yaml)
  end
end




