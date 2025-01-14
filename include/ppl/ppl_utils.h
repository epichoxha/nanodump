#pragma once

#include <windows.h>
#include <winternl.h>

#include "utils.h"
#include "dinvoke.h"
#include "syscalls.h"
#include "ppl/ppl_utils.h"
#include "ppl/ppl.h"

#define DIRECTORY_QUERY 0x0001
#define DIRECTORY_TRAVERSE 0x0002
#define DIRECTORY_CREATE_OBJECT 0x0004
#define DIRECTORY_CREATE_SUBDIRECTORY 0x0008
#define DIRECTORY_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | 0xF)
#define SYMBOLIC_LINK_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | 0x1)

#define SYMBOLIC_LINK_QUERY 0x0001

#if defined(_MSC_VER)

#define FileStandardInformation 5
#define ThreadImpersonationToken 5

typedef struct _FILE_STANDARD_INFORMATION {
  LARGE_INTEGER AllocationSize;
  LARGE_INTEGER EndOfFile;
  ULONG         NumberOfLinks;
  BOOLEAN       DeletePending;
  BOOLEAN       Directory;
} FILE_STANDARD_INFORMATION, *PFILE_STANDARD_INFORMATION;

#endif

BOOL token_get_sid(
    IN HANDLE hToken,
    OUT PSID* ppSid);

BOOL token_get_sid_as_string(
    IN HANDLE hToken,
    OUT LPWSTR* ppwszStringSid);

BOOL is_current_user_system(
    OUT PBOOL pbResult);

BOOL token_compare_sids(
    IN PSID pSidA,
    IN PSID pSidB);

BOOL token_is_not_restricted(
    IN HANDLE hToken,
    OUT PBOOL pbIsNotRestricted);

BOOL token_get_username(
    IN HANDLE hToken,
    OUT LPWSTR* ppwszUsername);

BOOL is_win_8_point_1_or_grater(VOID);

BOOL is_win_10_or_grater(VOID);

BOOL object_manager_create_directory(
    IN LPWSTR dirname,
    OUT PHANDLE hDirectory);

BOOL object_manager_create_symlik(
    IN LPWSTR linkname,
    IN LPWSTR targetname,
    OUT PHANDLE hLink);

BOOL check_known_dll_symbolic_link(
    IN LPCWSTR pwszDllName,
    IN LPWSTR pwszTarget);

BOOL get_file_size(
    IN HANDLE hFile,
    OUT PDWORD file_size);
