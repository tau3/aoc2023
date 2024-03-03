#include "day12.hpp"
#include "util.hpp"
#include <cstddef>
#include <deque>
#include <vector>

using namespace std;

int count_arrangements(const string &, const deque<size_t> &);
deque<size_t> to_groups(const string &);

int solve(const vector<string> &input) {
  int result = 0;
  for (const string &line : input) {
    const vector<string> tokens = split(line, " ");
    const string &springs = tokens[0];
    const deque<size_t> groups = to_groups(tokens[1]);
    result += count_arrangements(springs, groups);
  }
  return result;
}

deque<size_t> to_groups(const string &line) {
  const vector<string> tokens = split(line, ",");
  deque<size_t> result;
  for (const string &token : tokens) {
    result.push_back(stoi(token));
  }
  return result;
}

deque<size_t> copy_pop(const deque<size_t> &values) {
  deque<size_t> result = values;
  result.pop_front();
  return result;
}

bool fits_group(const string &line) {
  for (auto c : line) {
    if (c == '.') {
      return false;
    }
  }
  return true;
}

int count_arrangements(const string &springs, const deque<size_t> &groups) {
  if (groups.empty() || springs.empty()) {
    return 0;
  }

  size_t group = *groups.begin();
  if (springs.size() < group) {
    return 0;
  }

  if (fits_group(springs.substr(0))) {
    if (springs.length() > group) {
      if (springs[group] == '.') {
        return 1 +
               count_arrangements(springs.substr(group + 1), copy_pop(groups));
      } else {
        return count_arrangements(springs.substr(1), groups);
      }
    } else {
      return 1 + count_arrangements(springs.substr(group), copy_pop(groups));
    }
  }
  return count_arrangements(springs.substr(1), groups);
}
