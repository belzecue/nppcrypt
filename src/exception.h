/*
This file is part of nppcrypt
(http://www.github.com/jeanpaulrichter/nppcrypt)
a plugin for notepad++ [ Copyright (C)2003 Don HO <don.h@free.fr> ]
(https://notepad-plus-plus.org)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/

#ifndef EXCEPTION_H_DEF
#define EXCEPTION_H_DEF

#include <string>
#include <sstream>
#include <exception>
#include <vector>

class ExcError : public std::exception
{
public:
    enum class ID : unsigned {
        unexpected,
        no_scintilla_pointer,
        no_scintilla_handle,
        no_file_path,
        utf8conversion,
        wchar_conversion,
        preffile_read,
        preffile_parse,
        header_write_failed,
        failed_to_write_file,
        failed_to_read_file
    };
    ExcError(ID id, const char* func, unsigned int line) noexcept;
    const char *what() const noexcept {
        return msg.c_str();
    };
private:
    ID id;
    unsigned int line;
    std::string msg;
    static const char* messages[];
};

class ExcInvalid : public std::exception
{
public:
    enum class ID : unsigned {
        invalid_keypreset_id,
        invalid_mode,
        invalid_keylength,
        invalid_pbkdf2,
        invalid_bcrypt,
        invalid_scrypt,
        invalid_saltlength,
        invalid_bcrypt_saltlength,
        invalid_linelength,
        invalid_hash_digestlen,
        invalid_header,
        invalid_header_version,
        invalid_hmac_data,
        invalid_hmac_hash,
        invalid_cipher,
        invalid_encoding,
        invalid_keyderivation,
        invalid_salt,
        invalid_iv,
        invalid_tag,
        invalid_aad_flag,
        invalid_hash,
        invalid_hash_key,
        invalid_cmdline_action,
        invalid_convert_target_enc,
        invalid_eol,
        invalid_uppercase,
        missing_header,
        missing_keylength,
        missing_cipher_mode,
        missing_hmac_key,
        missing_iv,
        missing_salt,
        missing_password,
        hash_without_keysupport,
        hash_requires_key,
        cmdline_only_utf8
    };
    ExcInvalid(ID id) noexcept : id(id) {};
    const char *what() const noexcept {
        return messages[(unsigned)id];
    };
    ID getID() { return id; };
private:
    ID id;
    static const char* messages[];
};

class ExcInfo : public std::exception
{
public:
    enum class ID : unsigned {
        file_empty,
        hmac_auth_failed,
        bad_header_version,
        no_text_selected,
        no_convert_text_selected
    };
    ExcInfo(ID id) noexcept : id(id) {};
    const char *what() const noexcept {
        return messages[(unsigned)id];
    };
    ID getID() { return id; };
    const char* getURL() { return urls[(unsigned)id]; };
    const char* getURLCaption() { return url_captions[(unsigned)id]; };
private:
    ID id;
    static const char* messages[];
    static const char* urls[];
    static const char* url_captions[];
};

#define throwError(id) throw ExcError(ExcError::ID::id, __func__, __LINE__);
#define throwInvalid(id) throw ExcInvalid(ExcInvalid::ID::id);
#define throwInfo(id) throw ExcInfo(ExcInfo::ID::id);

#endif