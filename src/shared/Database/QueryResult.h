/*
 * This file is part of the OregonCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef QUERYRESULT_H
#define QUERYRESULT_H

#include <ace/Refcounted_Auto_Ptr.h>
#include <ace/Null_Mutex.h>

#include "Field.h"
#include "Log.h"

#ifdef WIN32
  #include <winsock2.h>
#endif
#include <mysql.h>

class QueryResult
{
    public:
        QueryResult(MYSQL_RES *result, MYSQL_FIELD *fields, uint64 rowCount, uint32 fieldCount);
        ~QueryResult();

        bool NextRow();

        Field *Fetch() const { return mCurrentRow; }

        const Field & operator [] (int index) const { return mCurrentRow[index]; }

        uint32 GetFieldCount() const { return mFieldCount; }
        uint64 GetRowCount() const { return mRowCount; }

    protected:
        Field *mCurrentRow;
        uint32 mFieldCount;
        uint64 mRowCount;

    private:
        enum Field::DataTypes ConvertNativeType(enum_field_types mysqlType) const;
        void EndQuery();
        MYSQL_RES *mResult;

};

typedef ACE_Refcounted_Auto_Ptr<QueryResult, ACE_Null_Mutex> QueryResult_AutoPtr;

typedef std::vector<std::string> QueryFieldNames;

class QueryNamedResult
{
    public:
        explicit QueryNamedResult(QueryResult* query, QueryFieldNames const& names) : mQuery(query), mFieldNames(names) {}
        ~QueryNamedResult() { delete mQuery; }

        // compatible interface with QueryResult
        bool NextRow() { return mQuery->NextRow(); }
        Field *Fetch() const { return mQuery->Fetch(); }
        uint32 GetFieldCount() const { return mQuery->GetFieldCount(); }
        uint64 GetRowCount() const { return mQuery->GetRowCount(); }
        Field const& operator[] (int index) const { return (*mQuery)[index]; }

        // named access
        Field const& operator[] (const std::string &name) const { return mQuery->Fetch()[GetField_idx(name)]; }
        QueryFieldNames const& GetFieldNames() const { return mFieldNames; }

        uint32 GetField_idx(const std::string &name) const
        {
            for (size_t idx = 0; idx < mFieldNames.size(); ++idx)
            {
                if (mFieldNames[idx] == name)
                    return idx;
            }
            ASSERT(false && "unknown field name");
            return uint32(-1);
        }

    protected:
        QueryResult *mQuery;
        QueryFieldNames mFieldNames;
};

class ResultBind
{
    friend class PreparedResultSet;
    public:

        ResultBind(MYSQL_STMT* stmt) : m_stmt(stmt), m_fieldCount(NULL), m_isNull(NULL), m_length(NULL), m_rBind(NULL) {}
        ~ResultBind()
        {
            if (!m_fieldCount)
                return;

            CleanUp();  // Clean up buffer
            mysql_stmt_free_result(m_stmt);
        }

        void BindResult(uint32& num_rows);

    protected:
        MYSQL_BIND* m_rBind;
        MYSQL_STMT* m_stmt;
        MYSQL_RES* m_res;

        void FreeBindBuffer();
        bool IsValidIndex(uint32 index) { return index < m_fieldCount; }

    private:

        void CleanUp();

        size_t SizeForType(MYSQL_FIELD* field)
        {
            switch (field->type)
            {
                case MYSQL_TYPE_NULL:
                    return 0;
                case MYSQL_TYPE_TINY:
                    return 1;
                case MYSQL_TYPE_YEAR:
                case MYSQL_TYPE_SHORT:
                    return 2;
                case MYSQL_TYPE_INT24:
                case MYSQL_TYPE_LONG:
                case MYSQL_TYPE_FLOAT:
                    return 4;
                case MYSQL_TYPE_DOUBLE:
                case MYSQL_TYPE_LONGLONG:
                case MYSQL_TYPE_BIT:
                    return 8;

                case MYSQL_TYPE_TIMESTAMP:
                case MYSQL_TYPE_DATE:
                case MYSQL_TYPE_TIME:
                case MYSQL_TYPE_DATETIME:
                    return sizeof(MYSQL_TIME);

                case MYSQL_TYPE_TINY_BLOB:
                case MYSQL_TYPE_MEDIUM_BLOB:
                case MYSQL_TYPE_LONG_BLOB:
                case MYSQL_TYPE_BLOB:
                case MYSQL_TYPE_STRING:
                case MYSQL_TYPE_VAR_STRING:
                    return field->max_length + 1;

                case MYSQL_TYPE_DECIMAL:
                case MYSQL_TYPE_NEWDECIMAL:
                    return 64;

                case MYSQL_TYPE_GEOMETRY:
                /* 
                Following types are not sent over the wire:
                MYSQL_TYPE_ENUM:
                MYSQL_TYPE_SET:
                */
                default:
                    sLog.outSQLDriver("ResultBind::SizeForType(): invalid field type %u", uint32(field->type));
                    return 0;
            }
        }

        my_bool* m_isNull;
        unsigned long* m_length;
        uint32 m_fieldCount;
};

class PreparedResultSet
{
    template<class T> friend class DatabaseWorkerPool;
    public:
        PreparedResultSet(MYSQL_STMT* stmt) : num_rows(0), row_position(0)
        {
            rbind = new ResultBind(stmt);
            rbind->BindResult(num_rows);
        }
        ~PreparedResultSet()
        {
            delete rbind;
        }

        operator bool() { return num_rows > 0; }

        uint8 GetUInt8(uint32 index);
        int8 GetInt8(uint32 index);
        uint16 GetUInt16(uint32 index);
        int16 GetInt16(uint32 index);
        uint32 GetUInt32(uint32 index);
        int32 GetInt32(uint32 index);
        float GetFloat(uint32 index);
        std::string GetString(uint32 index);

        bool NextRow()
        {
            if (row_position >= num_rows)
                return false;

            int retval = mysql_stmt_fetch( rbind->m_stmt );
                
            if (!retval || retval == MYSQL_DATA_TRUNCATED)
                retval = true;

            if (retval == MYSQL_NO_DATA)
                retval = false;

            ++row_position;
            return retval;
        }

    private:
        bool CheckFieldIndex(uint32 index)  const
        {   
            if (!rbind->IsValidIndex(index))
                return false;
        
            if (rbind->m_isNull[index])
                return false;

            return true;
        }

        ResultBind* rbind;
        uint32 row_position;
        uint32 num_rows;
};

#endif

