n=gets.to_i
a=gets.split.map(&:to_i)
puts(a.max*2<a.inject(:+)?"Yes":"No")
