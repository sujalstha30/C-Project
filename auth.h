#ifndef AUTH_H
#define AUTH_H

#define MAX_LOGIN_ATTEMPTS 3

int login();
void logout(int *logged_in);
int verify_pin(int account_index);
int is_logged_in();

#endif