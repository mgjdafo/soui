#include <SApp.h>

wchar_t * cast_a2w(char * str)
{
    return (wchar_t *)str;
}

int Utf8ToW(lua_State* L)
{
    size_t n = 0;
    char* str = (char*)luaL_checklstring(L, -1, &n);
    if(!str)   return 0;
    SStringW strW=S_CA2W(str,CP_UTF8);
    lua_pushlstring(L, (const char*)(LPCWSTR)strW, 2*strW.GetLength()+2);
    return 1;
}

TCHAR * cast_a2t(char * str)
{
    return (TCHAR *)str;
}


int Utf8ToT(lua_State *L)
{
    size_t n = 0;
    char* str = (char*)luaL_checklstring(L, -1, &n);
    if(!str)   return 0;
    SStringT strT=S_CA2T(str,CP_UTF8);
    lua_pushlstring(L, (const char*)(LPCTSTR)strT, (strT.GetLength()+1)*sizeof(TCHAR));
    return 1;
}

BOOL reg_global(lua_State *L)
{
	try{
        lua_register(L, "A2W", Utf8ToW);
        fflua_register_t<>(L)
            .def(&cast_a2w, "cast_a2w");                //! 注册全局函数
        luaL_dostring(L,"function L (str)\n return cast_a2w(A2W(str));\nend");//注册一个全局的"L"函数，用来将utf8编码的字符串转换为WCHAR
        
        lua_register(L, "A2T", Utf8ToT);
        fflua_register_t<>(L)
            .def(&cast_a2t, "cast_a2t");                //! 注册全局函数
        luaL_dostring(L,"function T (str)\n return cast_a2t(A2T(str));\nend");//注册一个全局的"T"函数，用来将utf8编码的字符串转换为TCHAR
		return TRUE;
	}catch(...)
	{
		return FALSE;
	}
}