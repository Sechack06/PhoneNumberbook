#include "cryptogram.h"
#include "time.h"
#include "user.h"

extern USER thisuserifm;

PERSONLIST makecryptogram(PERSONLIST data)
{
	PERSONLIST cryptogram;
	strcpy(cryptogram.Path, encoding(data.Path));
	strcpy(cryptogram.FileName, encoding(data.FileName));
	strcpy(cryptogram.name, encoding(data.name));
	strcpy(cryptogram.phonenumber[0], encoding(data.phonenumber[0]));
	strcpy(cryptogram.phonenumber[1], encoding(data.phonenumber[1]));
	strcpy(cryptogram.phonenumber[2], encoding(data.phonenumber[2]));
	strcpy(cryptogram.email, encoding(data.email));
	strcpy(cryptogram.Mdomain, encoding(data.Mdomain));
	strcpy(cryptogram.homeadress, encoding(data.homeadress));
	strcpy(cryptogram.etc, encoding(data.etc));

	return cryptogram;
}
PERSONLIST decryptpsl(PERSONLIST cryptogram)
{
	PERSONLIST data;
	strcpy(data.Path, encoding(cryptogram.Path));
	strcpy(data.FileName, encoding(cryptogram.FileName));
	strcpy(data.name, encoding(cryptogram.name));
	strcpy(data.phonenumber[0], encoding(cryptogram.phonenumber[0]));
	strcpy(data.phonenumber[1], encoding(cryptogram.phonenumber[1]));
	strcpy(data.phonenumber[2], encoding(cryptogram.phonenumber[2]));
	strcpy(data.email, encoding(cryptogram.email));
	strcpy(data.Mdomain, encoding(cryptogram.Mdomain));
	strcpy(data.homeadress, encoding(cryptogram.homeadress));
	strcpy(data.etc, encoding(cryptogram.etc));

	return data;
}
char* encoding(char string[])
{
	char cryptogram[1000] = { 0 };
	strcpy(cryptogram, string);
	for (unsigned int i = 0; i < strlen(cryptogram); i++)
	{
		cryptogram[i] = cryptogram[i] ^ thisuserifm.key;
	}
	return cryptogram;
}
int makekey()
{
	int key = 0;
	srand(time(NULL));
	key = rand();

	return key;
}
USER usermakecryptogram(USER userdata)
{
	USER thisuser;
	strcpy(thisuser.name, userencoding(userdata.name, userdata.key));
	strcpy(thisuser.id, userencoding(userdata.id, userdata.key));
	strcpy(thisuser.password, userencoding(userdata.password, userdata.key));
	strcpy(thisuser.userdatapath, userencoding(userdata.userdatapath, userdata.key));
	strcpy(thisuser.userpath, userencoding(userdata.userpath, userdata.key));
	thisuser.key = userdata.key ^ 77;

	return thisuser;
}
char* userencoding(char string[], int key)
{
	char cryptogram[1000] = { 0 };
	strcpy(cryptogram, string);

	for (unsigned int i = 0; i < strlen(cryptogram); i++)
	{
		cryptogram[i] = cryptogram[i] ^ key;
	}
	return cryptogram;
}
USER userdecryptpsl(USER crpdata)
{
	USER dcdata;
	dcdata.key = crpdata.key ^ 77;
	strcpy(dcdata.name, userencoding(crpdata.name, dcdata.key));
	strcpy(dcdata.id, userencoding(crpdata.id, dcdata.key));
	strcpy(dcdata.password, userencoding(crpdata.password, dcdata.key));
	strcpy(dcdata.userdatapath, userencoding(crpdata.userdatapath, dcdata.key));
	strcpy(dcdata.userpath, userencoding(crpdata.userpath, dcdata.key));

	return dcdata;
}