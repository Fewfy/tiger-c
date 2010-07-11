#include <stdlib.h>

#include "env.h"

env_entry_t env_var_entry(type_t type)
{
    env_entry_t p = checked_malloc(sizeof(*p));
    p->kind = ENV_VAR_ENTRY;
    p->u.var.type = type;
    return p;
}

env_entry_t env_func_entry(list_t formals, type_t result)
{
    env_entry_t p = checked_malloc(sizeof(*p));
    p->kind = ENV_FUNC_ENTRY;
    p->u.func.formals = formals;
    p->u.func.result = result;
    return p;
}

table_t env_base_tenv(void)
{
    table_t tab = sym_empty();
    sym_enter(tab, symbol("int"), ty_int());
    sym_enter(tab, symbol("string"), ty_string());
    return tab;
}

table_t env_base_venv(void)
{
    table_t tab = sym_empty();
    sym_enter(tab, symbol("getchar"), env_func_entry(NULL, ty_string()));
    sym_enter(tab, symbol("ord"), env_func_entry(list(ty_string(), NULL), ty_int()));
    sym_enter(tab, symbol("print"), env_func_entry(list(ty_string(), NULL), ty_void()));
    sym_enter(tab, symbol("chr"), env_func_entry(list(ty_int(), NULL), ty_string()));
    return tab;
}