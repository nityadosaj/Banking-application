#ifndef USERSTRUCT_H
#define USERSTRUCT_H

#include <string>
using namespace std;

struct User 
{
  string userName;
  string email;
  string password;
  string firstName;
  string lastName;
  string dob;
  string** security;  //3/2 array
} ; 


#endif