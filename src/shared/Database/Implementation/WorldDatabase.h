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

#ifndef _WORLDDATABASE_H
#define _WORLDDATABASE_H

#include "DatabaseWorkerPool.h"
#include "MySQLConnection.h"

class WorldDatabaseConnection : public MySQLConnection
{
    public:
        //- Constructors for sync and async connections
        WorldDatabaseConnection() : MySQLConnection() {}
        WorldDatabaseConnection(ACE_Activation_Queue* q) : MySQLConnection(q) {}

        //- Loads databasetype specific prepared statements
        bool Open(const std::string& infoString);
};

typedef DatabaseWorkerPool<WorldDatabaseConnection> WorldDatabaseWorkerPool;

enum WorldDatabaseStatements
{
    WORLD_DEL_CRESPAWNTIME,
    WORLD_ADD_CRESPAWNTIME,
    MAX_WORLDDATABASE_STATEMENTS,
};

#endif