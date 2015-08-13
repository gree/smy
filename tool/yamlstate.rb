require 'pp'
require 'yaml'

class YamlState
	attr_reader :nodes, :links

	class Node
		attr_reader :name, :link, :rlink

		def initialize(name)
			@name = name
			@link = Array.new
			@rlink = Array.new
		end

		def add(link)
			if link.from == self
				@link.push link
			else
				@rlink.push link
			end
		end
	end

	class Link
		attr_reader :from, :to, :condition, :comment, :spawn

		def initialize(from, to, condition, comment, spawn = false)
			@condition = condition
			@comment = comment
			@spawn = spawn
			set_from(from)
			set_to(to)
		end

		def set_to(to)
			@to = to
			@to.add(self)
		end

		def set_from(from)
			@from = from
			@from.add(self)
		end
	end

	def initialize
		@nodes = Array.new
		@links = Array.new
	end

	def add(path)
    data = YAML.load(File.read(path))
    nodes_hash = {}
    data.each do | name_from, lines |
      nodes_hash[name_from] = Node.new(name_from)
    end
    data.each do | name_from, lines |
      next if lines.nil?
      lines.each do | name_to, comment |
        nodes_hash[name_to] = Node.new(name_to)
      end
    end
    
    @nodes = nodes_hash.values

    data.each do | name_from, lines |
      next if lines.nil?
      lines.each do | name_to, info |
        condition = comment = nil
        unless info.nil?
          condition = info["when"]
          comment = info["comment"]
        end
        @links.push Link.new(nodes_hash[name_from], nodes_hash[name_to], condition, comment)
      end
    end
	end
end
