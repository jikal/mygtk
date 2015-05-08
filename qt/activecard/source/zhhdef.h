#pragma once
#include <vector>
#include <string>
using namespace std;

#define  USER_LOGIN_URI  "https://terminal.vingoojuice.com/card/user_login" //用户登录
#define  BARD_LIST_URI   "https://terminal.vingoojuice.com/card/get_brand"  //根据用户ID获取辖区列表
#define  GET_CARDTYPE_URI   "https://terminal.vingoojuice.com/card/get_card_type" //获取卡片类型列表
#define  INSERT_CARD_URI "https://terminal.vingoojuice.com/card/insert_card"  //插入卡信息

#define MAX_URLRECVBUF_LEN 1024*5

typedef struct USER_INFO{
	string id;
	string name;
	string position;
	string brand_name;
	USER_INFO()
	{
		id = "";
		name = "";
		position = "";
		brand_name = "";
	}
}S_USER_INFO;

typedef struct USER_LOGIN_INFO{
	string return_code;
	string return_msg;
	vector<S_USER_INFO> vUserInfo;
	USER_LOGIN_INFO()
	{
		return_code = "";
		return_msg = "";
		vUserInfo.clear();
	}
}S_USER_LOGIN_INFO;


typedef struct BRAND_INFO
{
	string id;
	string brand_name;
	BRAND_INFO()
	{
		id = "";
		brand_name = "";
	}
}S_BRAND_INFO;

typedef struct CARD_BRAND_INFO
{
	string return_code;
	vector<S_BRAND_INFO> vBrandInfo;
	CARD_BRAND_INFO()
	{
		return_code = "";
		vBrandInfo.clear();
	}
}S_CARD_BRAND_INFO;

typedef struct CARD_TYPE
{
	string id;
	string type_name;
	CARD_TYPE()
	{
		id = "";
		type_name = "";
	}
}S_CARD_TYPE;

typedef struct CARD_TYPE_INFO
{
	string return_code;
	vector<S_CARD_TYPE> vCardType;
    CARD_TYPE_INFO()
	{
		return_code = "";
		vCardType.clear();
	}
}S_CARD_TYPE_INFO;

typedef struct INSERT_CARD_INFO
{
	string id_out;
	string id_in;
	string id_code;
	string card_type;
	string brand_id;
	string card_value;
	string card_checkout;
	string remark;
	INSERT_CARD_INFO()
	{
		id_out = "";
		id_in = "";
		id_code = "";
		card_type = "";
		brand_id = "";
		card_value = "";
		card_checkout = "";
		remark= "";
	}
}S_INSERT_CARD_INFO;