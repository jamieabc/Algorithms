# First attempt, time complexity is O(n), space complexity is O(n)
def run(str, length)
  sping = str.slice!(0, length)
  str + sping
end
# puts run('123456', 2)

# Key point is space complexity, cannot use additional memory space.
# It means space can be reused.
