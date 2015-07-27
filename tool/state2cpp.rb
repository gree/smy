#!/usr/local/bin/macruby

require File.dirname($0) + '/grafstate.rb'
require 'pp'

argv = ARGV
T = argv.shift
header = File.open(T + "State.h", "w")
source = File.open(T + "State.cpp", "w")

data = GraffleState.new
argv.each do |file|
  data.add(file)
end
data.compile

root = Array.new
data.nodes.delete_if do |node|
  if node.rlink.empty?
    node.link.each do |link|
      root.push link
    end
    true
  else
    false
  end
end

n = 0
while true
  break if n == data.nodes.length
  if data.nodes[n].rlink.empty?
    data.nodes[n].link.each do |l|
      link = l
      link.set_name data.nodes[n].name + " " + link.name
      root.push link
    end
    data.nodes.delete_at n
  else
    n += 1
  end
end

header.print <<END
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

private:
	StateMachine _stateMachine;
public:
	void StartState();
	void ExecState();
	std::string DumpState() const;
private:
END

source.print <<END
#include "#{T}.h"

void #{T}::StartState()
{
END

root.each do |link|
  funcname = link.to.name.split.shift.sub(/^\*/, "")
  comment = link.name.empty? ? "" : " // #{link.name}"
  source.print <<END
	SPAWN(State#{funcname});#{comment}
END
end

source.print <<END
}

std::string #{T}::DumpState() const
{
	return TO_STRING();
}

void #{T}::ExecState()
{
	EXEC();
}
END

data.nodes.sort{|a,b| aname = a.name.sub(/^\*/, ""); bname = b.name.sub(/^\*/, ""); aname <=> bname}.each do |n|
  name = n.name.split
  funcname = name.shift.sub(/^\*/, "")
  comment = name.join(" ")

  header.print <<END
	void State#{funcname}();
END

  source.print <<END

void #{T}::State#{funcname}()
{
	// TODO
END

  unless comment.empty?
    source.print <<END
	// #{comment}.
END
  end

  condition = Hash.new
  n.link.each do |link|
    condition[link.name] ||= Array.new
    condition[link.name].push link.to
    #print funcname, "\t", link.name, "\t", link.to.name, "\n"
  end

  case condition.length
  when 0
    if n.name =~ /^\*/
    source.print <<END
	if (false)
		EXIT();
END
  else
    source.print <<END
	EXIT();
END
  end
  when 1
    if n.name =~ /^\*/
      indent = "\t"
      yield_to = false
      if condition.keys[0] != ""
        comment = condition.keys[0].gsub("\n", " ")
        if comment =~ /^\*/
          comment = comment[1..-1]
          yield_to = true 
        end
        comment = "\n\t\t// " + comment + "."
      else
        comment = ""
      end
      source.print <<END
	if (false) {#{comment}
END
    else
      indent = ""
    end

    condition[condition.keys[0]].sort{|a,b| aname = a.name.sub(/^\*/, ""); bname = b.name.sub(/^\*/, ""); aname <=> bname}.each do |n|
      nextname = n.name.split.shift.sub(/^\*/, "")
      source.print <<END
	#{indent}#{yield_to ? "YIELD_TO" : "SWITCH_TO"}(State#{nextname});
END
    end

    if indent != ""
      source.print <<END
	}
END
    end
  else
    count = 0
    condition.keys.each do |key|
      if key =~ /SPAWN/
        condition[key].sort{|a,b| aname = a.name.sub(/^\*/, ""); bname = b.name.sub(/^\*/, ""); aname <=> bname}.each do |n|
          nextname = n.name.split.shift.sub(/^\*/, "")
          source.print <<END
	SPAWN(State#{nextname});	// #{key.gsub("SPAWN", "").gsub("\n", " ")}.
END
        end
        source.puts
      end
    end

    condition.keys.each do |key|
      next if key =~ /SPAWN/
      yield_to = false
      comment = key.gsub("\n", " ")
      if comment =~ /^\*/
        comment = comment[1..-1]
        yield_to = true 
      end
      if count == 0
        source.print <<END
	if (false) {
		// #{comment}.
END
      else
        source.print <<END
	} else if (false) {
		// #{comment}.
END
      end
      count += 1

      condition[key].sort{|a,b| aname = a.name.sub(/^\*/, ""); bname = b.name.sub(/^\*/, ""); aname <=> bname}.each do |n|
        nextname = n.name.split.shift.sub(/^\*/, "")
        source.print <<END
		#{yield_to ? "YIELD_TO" : "SWITCH_TO"}(State#{nextname});
END
      end
    end
    source.print <<END
	}
END
  end

  source.print <<END
}
END
end

header.print <<END

END
