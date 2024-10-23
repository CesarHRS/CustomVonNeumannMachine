#ifndef __HASHREGISTER_HPP
#define __HASHREGISTER_HPP

#include<iostream>
#include <map>
#include <string>
#include<string>

using namespace std;

struct Map {
  std::map<string, string> mp;

  
   Map() { // vai funcionar como construtor para preenche-lo inicialmente
    
    mp["00000"] = "zero";
    mp["00010"] = "v0";
    mp["00011"] = "v1";
    mp["00100"] = "a0";
    mp["00101"] = "a1";
    mp["00110"] = "a2";
    mp["00111"] = "a3";
    mp["01000"] = "t0";
    mp["01001"] = "t1";
    mp["01010"] = "t2";
    mp["01011"] = "t3";
    mp["01100"] = "t4";
    mp["01101"] = "t5";
    mp["01110"] = "t6";
    mp["01111"] = "t7";
    mp["10000"] = "s0";
    mp["10001"] = "s1";
    mp["10010"] = "s2";
    mp["10011"] = "s3";
    mp["10100"] = "s4";
    mp["10101"] = "s5";
    mp["10110"] = "s6";
    mp["10111"] = "s7";
    mp["11000"] = "t8";
    mp["11001"] = "t9";
    mp["11010"] = "k0";
    mp["11011"] = "k1";
    mp["11100"] = "gp";
    mp["11101"] = "sp";
    mp["11110"] = "fp";
    mp["11111"] = "ra";


   }
  string getRegister(string codeofregister);
};

#endif