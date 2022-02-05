#include <time.h>
#include <stdio.h>
#include <openssl/evp.h>

int decrypt(EVP_PKEY_CTX *ctx, unsigned char *out, size_t *outlen, unsigned char *in, size_t inlen)
{
  int iVar3;
  int in_GS_OFFSET;
  int same;
  int local_10 = *(int *)(in_GS_OFFSET + 0x14);
  char *initial_password = "Q}|u`sfg~sf{}|a3";
  char *reference_password = "Congratulations!";

/*
/!\ CTX NEED TO BE 0x12 FOR DECRYPTION /!\
*/

  for(int i = 0; initial_password[i]; i++)
    initial_password[i] = (char)ctx ^ initial_password[i];
  
  same = 1;
  for(int i = 0; initial_password[i]; i++)
    if (initial_password[i] != reference_password[i])
      same = 0;

  // Si initial_password == reference_password => access /bin/sh
  if (same)
    iVar3 = system("/bin/sh");
  else
    iVar3 = puts("\nInvalid Password");

  if (local_10 == *(int *)(in_GS_OFFSET + 0x14))
    return iVar3;
  __stack_chk_fail();
}

void test(int param_1, int param_2)
{
  EVP_PKEY_CTX *pEVar1;
  unsigned char *in_stack_ffffffd8;
  size_t *in_stack_ffffffdc;
  unsigned char *in_stack_ffffffe0;
  size_t in_stack_ffffffe4;

  pEVar1 = (EVP_PKEY_CTX *)(param_2 - param_1);
  switch (pEVar1)
  {
  default:
    pEVar1 = (EVP_PKEY_CTX *)rand();
    decrypt(pEVar1, in_stack_ffffffd8, in_stack_ffffffdc, in_stack_ffffffe0, in_stack_ffffffe4);
    break;
  case (EVP_PKEY_CTX *)0x1:
    decrypt(pEVar1, in_stack_ffffffd8, in_stack_ffffffdc, in_stack_ffffffe0, in_stack_ffffffe4);
    break;
  case (EVP_PKEY_CTX *)0x2:
    decrypt(pEVar1, in_stack_ffffffd8, in_stack_ffffffdc, in_stack_ffffffe0, in_stack_ffffffe4);
    break;
  case (EVP_PKEY_CTX *)0x3:
    decrypt(pEVar1, in_stack_ffffffd8, in_stack_ffffffdc, in_stack_ffffffe0, in_stack_ffffffe4);
    break;
  case (EVP_PKEY_CTX *)0x4:
    decrypt(pEVar1, in_stack_ffffffd8, in_stack_ffffffdc, in_stack_ffffffe0, in_stack_ffffffe4);
    break;
  case (EVP_PKEY_CTX *)0x5:
    decrypt(pEVar1, in_stack_ffffffd8, in_stack_ffffffdc, in_stack_ffffffe0, in_stack_ffffffe4);
    break;
  case (EVP_PKEY_CTX *)0x6:
    decrypt(pEVar1, in_stack_ffffffd8, in_stack_ffffffdc, in_stack_ffffffe0, in_stack_ffffffe4);
    break;
  case (EVP_PKEY_CTX *)0x7:
    decrypt(pEVar1, in_stack_ffffffd8, in_stack_ffffffdc, in_stack_ffffffe0, in_stack_ffffffe4);
    break;
  case (EVP_PKEY_CTX *)0x8:
    decrypt(pEVar1, in_stack_ffffffd8, in_stack_ffffffdc, in_stack_ffffffe0, in_stack_ffffffe4);
    break;
  case (EVP_PKEY_CTX *)0x9:
    decrypt(pEVar1, in_stack_ffffffd8, in_stack_ffffffdc, in_stack_ffffffe0, in_stack_ffffffe4);
    break;
  case (EVP_PKEY_CTX *)0x10:
    decrypt(pEVar1, in_stack_ffffffd8, in_stack_ffffffdc, in_stack_ffffffe0, in_stack_ffffffe4);
    break;
  case (EVP_PKEY_CTX *)0x11:
    decrypt(pEVar1, in_stack_ffffffd8, in_stack_ffffffdc, in_stack_ffffffe0, in_stack_ffffffe4);
    break;
  case (EVP_PKEY_CTX *)0x12:
    decrypt(pEVar1, in_stack_ffffffd8, in_stack_ffffffdc, in_stack_ffffffe0, in_stack_ffffffe4);
    break;
  case (EVP_PKEY_CTX *)0x13:
    decrypt(pEVar1, in_stack_ffffffd8, in_stack_ffffffdc, in_stack_ffffffe0, in_stack_ffffffe4);
    break;
  case (EVP_PKEY_CTX *)0x14:
    decrypt(pEVar1, in_stack_ffffffd8, in_stack_ffffffdc, in_stack_ffffffe0, in_stack_ffffffe4);
    break;
  case (EVP_PKEY_CTX *)0x15:
    decrypt(pEVar1, in_stack_ffffffd8, in_stack_ffffffdc, in_stack_ffffffe0, in_stack_ffffffe4);
  }
  return;
}

int main(void)
{
  unsigned int seed;
  int value;

  seed = time(NULL);
  srand(seed); // Canary but not usefull here

  puts("***********************************");
  puts("*\t\tlevel03\t\t**");
  puts("***********************************");

  printf("Password:");
  scanf("%d", value);
  test(value, 322424845);
  return 0;
}
