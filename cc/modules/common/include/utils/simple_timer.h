// ==============================================================================
// Copyright 2020 The LatticeX Foundation
// This file is part of the Rosetta library.
//
// The Rosetta library is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// The Rosetta library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with the Rosetta library. If not, see <http://www.gnu.org/licenses/>.
// ==============================================================================
#pragma once
#include <chrono>

class SimpleTimer {
 public:
  SimpleTimer() { start(); }
  virtual ~SimpleTimer() {}

  void start() {
    begin = std::chrono::steady_clock::now();
    end = begin;
    stoped = false;
  }

  double stop() {
    end = std::chrono::steady_clock::now();
    stoped = true;
    std::chrono::duration<double> elapsed_seconds = end - begin;
    double costTime = elapsed_seconds.count();
    return costTime;
  }

  double elapse() const {
    auto ending = std::chrono::steady_clock::now();
    if (stoped)
      ending = end;
    std::chrono::duration<double> elapsed_seconds = ending - begin;
    return elapsed_seconds.count();
  }

  long long int ms_elapse() const {
    auto ending = std::chrono::steady_clock::now();
    if (stoped)
      ending = end;
    std::chrono::duration<long long int, std::micro> elapsed_milliseconds =
      std::chrono::duration_cast<std::chrono::duration<long long int, std::milli>>(ending - begin);
    return elapsed_milliseconds.count();
  }

  long long int us_elapse() const {
    auto ending = std::chrono::steady_clock::now();
    if (stoped)
      ending = end;
    std::chrono::duration<long long int, std::micro> elapsed_microseconds =
      std::chrono::duration_cast<std::chrono::duration<long long int, std::micro>>(ending - begin);
    return elapsed_microseconds.count();
  }

  long long int ns_elapse() const {
    auto ending = std::chrono::steady_clock::now();
    if (stoped)
      ending = end;
    std::chrono::duration<long long int, std::nano> elapsed_microseconds =
      std::chrono::duration_cast<std::chrono::duration<long long int, std::nano>>(ending - begin);
    return elapsed_microseconds.count();
  }

 private:
  bool stoped;
  std::chrono::time_point<std::chrono::steady_clock> begin;
  std::chrono::time_point<std::chrono::steady_clock> end;
};
