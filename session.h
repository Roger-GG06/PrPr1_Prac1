#ifndef SESSION_H
#define SESSION_H

#include "structs.h"
#include "utilsFun.h"

void loadUsers(user *users, int *userCount);
void saveUsers(user *users, int numUsers);
void initUsers(user *users, int *numUsers);

int findUserByUsername(user *users, int numUsers, char username[MAX_STR]);
int validatePassword(user u, char password[MAX_STR]);
int validatePin(user u, int pin);

int login(user *users, int numUsers);
int registerUser(user *users, int *numUsers);


#endif