/*
 * Copyright (C) 2008-2010 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * Copyright (C) 2009 Oregon <http://www.oregoncore.com/>
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

/* ScriptData
SDName: Dustwallow_Marsh
SD%Complete: 95
SDComment: Quest support: 11180, 558, 11126, 1173, 1273, 1324, Vendor Nat Pagle
SDCategory: Dustwallow Marsh
EndScriptData */

/* ContentData
mobs_risen_husk_spirit
npc_restless_apparition
npc_deserter_agitator
npc_lady_jaina_proudmoore
npc_nat_pagle
npc_morokk
npc_ogron
npc_private_hendel
EndContentData */

#include "ScriptPCH.h"
#include "ScriptedEscortAI.h"

/*######
## mobs_risen_husk_spirit
######*/

#define SPELL_SUMMON_RESTLESS_APPARITION    42511
#define SPELL_CONSUME_FLESH                 37933           //Risen Husk
#define SPELL_INTANGIBLE_PRESENCE           43127           //Risen Spirit

struct mobs_risen_husk_spiritAI : public ScriptedAI
{
    mobs_risen_husk_spiritAI(Creature *c) : ScriptedAI(c) {}

    uint32 ConsumeFlesh_Timer;
    uint32 IntangiblePresence_Timer;

    void Reset()
    {
        ConsumeFlesh_Timer = 10000;
        IntangiblePresence_Timer = 5000;
    }

    void EnterCombat(Unit* who) { }

    void DamageTaken(Unit *done_by, uint32 &damage)
    {
        if (done_by->GetTypeId() == TYPEID_PLAYER)
            if (damage >= me->GetHealth() && CAST_PLR(done_by)->GetQuestStatus(11180) == QUEST_STATUS_INCOMPLETE)
                me->CastSpell(done_by,SPELL_SUMMON_RESTLESS_APPARITION,false);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        if (ConsumeFlesh_Timer <= diff)
        {
            if (me->GetEntry() == 23555)
                DoCast(me->getVictim(),SPELL_CONSUME_FLESH);
            ConsumeFlesh_Timer = 15000;
        } else ConsumeFlesh_Timer -= diff;

        if (IntangiblePresence_Timer <= diff)
        {
            if (me->GetEntry() == 23554)
                DoCast(me->getVictim(),SPELL_INTANGIBLE_PRESENCE);
            IntangiblePresence_Timer = 20000;
        } else IntangiblePresence_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};
CreatureAI* GetAI_mobs_risen_husk_spirit(Creature* pCreature)
{
    return new mobs_risen_husk_spiritAI (pCreature);
}

/*######
## npc_restless_apparition
######*/

bool GossipHello_npc_restless_apparition(Player *player, Creature* pCreature)
{
    player->SEND_GOSSIP_MENU(player->GetGossipTextId(pCreature), pCreature->GetGUID());

    player->TalkedToCreature(pCreature->GetEntry(), pCreature->GetGUID());
    pCreature->SetInt32Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

    return true;
}

/*######
## npc_deserter_agitator
######*/

struct npc_deserter_agitatorAI : public ScriptedAI
{
    npc_deserter_agitatorAI(Creature *c) : ScriptedAI(c) {}

    void Reset()
    {
        me->setFaction(894);
    }

    void EnterCombat(Unit* who) {}
};

CreatureAI* GetAI_npc_deserter_agitator(Creature* pCreature)
{
    return new npc_deserter_agitatorAI (pCreature);
}

bool GossipHello_npc_deserter_agitator(Player *player, Creature* pCreature)
{
    if (player->GetQuestStatus(11126) == QUEST_STATUS_INCOMPLETE)
    {
        pCreature->setFaction(1883);
        player->TalkedToCreature(pCreature->GetEntry(), pCreature->GetGUID());
    }
    else
        player->SEND_GOSSIP_MENU(player->GetGossipTextId(pCreature), pCreature->GetGUID());

    return true;
}

/*######
## npc_lady_jaina_proudmoore
######*/

#define GOSSIP_ITEM_JAINA "I know this is rather silly but i have a young ward who is a bit shy and would like your autograph."

bool GossipHello_npc_lady_jaina_proudmoore(Player *player, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        player->PrepareQuestMenu(pCreature->GetGUID());

    if (player->GetQuestStatus(558) == QUEST_STATUS_INCOMPLETE)
        player->ADD_GOSSIP_ITEM(0, GOSSIP_ITEM_JAINA, GOSSIP_SENDER_MAIN, GOSSIP_SENDER_INFO);

    player->SEND_GOSSIP_MENU(player->GetGossipTextId(pCreature), pCreature->GetGUID());

    return true;
}

bool GossipSelect_npc_lady_jaina_proudmoore(Player *player, Creature* pCreature, uint32 sender, uint32 action)
{
    if (action == GOSSIP_SENDER_INFO)
    {
        player->SEND_GOSSIP_MENU(7012, pCreature->GetGUID());
        player->CastSpell(player, 23122, false);
    }
    return true;
}

/*######
## npc_nat_pagle
######*/

bool GossipHello_npc_nat_pagle(Player *player, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        player->PrepareQuestMenu(pCreature->GetGUID());

    if (pCreature->isVendor() && player->GetQuestRewardStatus(8227))
    {
        player->ADD_GOSSIP_ITEM(1, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
        player->SEND_GOSSIP_MENU(7640, pCreature->GetGUID());
    }
    else
        player->SEND_GOSSIP_MENU(7638, pCreature->GetGUID());

    return true;
}

bool GossipSelect_npc_nat_pagle(Player *player, Creature* pCreature, uint32 sender, uint32 action)
{
    if (action == GOSSIP_ACTION_TRADE)
        player->SEND_VENDORLIST(pCreature->GetGUID());

    return true;
}

/*######
## npc_morokk
######*/

enum
{
    SAY_MOR_CHALLENGE               = -1000499,
    SAY_MOR_SCARED                  = -1000500,

    QUEST_CHALLENGE_MOROKK          = 1173,

    FACTION_MOR_HOSTILE             = 168,
    FACTION_MOR_RUNNING             = 35
};

struct npc_morokkAI : public npc_escortAI
{
    npc_morokkAI(Creature* pCreature) : npc_escortAI(pCreature)
    {
        m_bIsSuccess = false;
        Reset();
    }

    bool m_bIsSuccess;

    void Reset() {}

    void WaypointReached(uint32 uiPointId)
    {
        switch(uiPointId)
        {
            case 0:
                SetEscortPaused(true);
                break;
            case 1:
                if (m_bIsSuccess)
                    DoScriptText(SAY_MOR_SCARED, me);
                else
                {
                    me->setDeathState(JUST_DIED);
                    me->Respawn();
                }
                break;
        }
    }

    void AttackedBy(Unit* pAttacker)
    {
        if (me->getVictim())
            return;

        if (me->IsFriendlyTo(pAttacker))
            return;

        AttackStart(pAttacker);
    }

    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    {
        if (HasEscortState(STATE_ESCORT_ESCORTING))
        {
            if (me->GetHealth()*100 < me->GetMaxHealth()*30.0f)
            {
                if (Player* pPlayer = GetPlayerForEscort())
                    pPlayer->GroupEventHappens(QUEST_CHALLENGE_MOROKK, me);

                me->setFaction(FACTION_MOR_RUNNING);
                SetRun(true);

                m_bIsSuccess = true;
                EnterEvadeMode();

                uiDamage = 0;
            }
        }
    }

    void UpdateEscortAI(const uint32 uiDiff)
    {
        if (!me->getVictim())
        {
            if (HasEscortState(STATE_ESCORT_PAUSED))
            {
                if (Player* pPlayer = GetPlayerForEscort())
                {
                    m_bIsSuccess = false;
                    DoScriptText(SAY_MOR_CHALLENGE, me, pPlayer);
                    me->setFaction(FACTION_MOR_HOSTILE);
                    AttackStart(pPlayer);
                }

                SetEscortPaused(false);
            }

            return;
        }

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_morokk(Creature* pCreature)
{
    return new npc_morokkAI(pCreature);
}

bool QuestAccept_npc_morokk(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_CHALLENGE_MOROKK)
    {
        if (npc_morokkAI* pEscortAI = CAST_AI(npc_morokkAI, pCreature->AI()))
            pEscortAI->Start(true, false, pPlayer->GetGUID(), pQuest);

        return true;
    }

    return false;
}


/*######
## npc_ogron
######*/

enum
{
    SAY_OGR_START                       = -1000452,
    SAY_OGR_SPOT                        = -1000453,
    SAY_OGR_RET_WHAT                    = -1000454,
    SAY_OGR_RET_SWEAR                   = -1000455,
    SAY_OGR_REPLY_RET                   = -1000456,
    SAY_OGR_RET_TAKEN                   = -1000457,
    SAY_OGR_TELL_FIRE                   = -1000458,
    SAY_OGR_RET_NOCLOSER                = -1000459,
    SAY_OGR_RET_NOFIRE                  = -1000460,
    SAY_OGR_RET_HEAR                    = -1000461,
    SAY_OGR_CAL_FOUND                   = -1000462,
    SAY_OGR_CAL_MERCY                   = -1000463,
    SAY_OGR_HALL_GLAD                   = -1000464,
    EMOTE_OGR_RET_ARROW                 = -1000465,
    SAY_OGR_RET_ARROW                   = -1000466,
    SAY_OGR_CAL_CLEANUP                 = -1000467,
    SAY_OGR_NODIE                       = -1000468,
    SAY_OGR_SURVIVE                     = -1000469,
    SAY_OGR_RET_LUCKY                   = -1000470,
    SAY_OGR_THANKS                      = -1000471,

    QUEST_QUESTIONING                   = 1273,

    FACTION_GENERIC_FRIENDLY            = 35,
    FACTION_THER_HOSTILE                = 151,

    NPC_REETHE                          = 4980,
    NPC_CALDWELL                        = 5046,
    NPC_HALLAN                          = 5045,
    NPC_SKIRMISHER                      = 5044,

    SPELL_FAKE_SHOT                     = 7105,

    PHASE_INTRO                         = 0,
    PHASE_GUESTS                        = 1,
    PHASE_FIGHT                         = 2,
    PHASE_COMPLETE                      = 3
};

static float m_afSpawn[] = {-3383.501953f, -3203.383301f, 36.149f};
static float m_afMoveTo[] = {-3371.414795f, -3212.179932f, 34.210f};

struct npc_ogronAI : public npc_escortAI
{
    npc_ogronAI(Creature* pCreature) : npc_escortAI(pCreature)
    {
        lCreatureList.clear();
        m_uiPhase = 0;
        m_uiPhaseCounter = 0;
        Reset();
    }

    std::list<Creature*> lCreatureList;

    uint32 m_uiPhase;
    uint32 m_uiPhaseCounter;
    uint32 m_uiGlobalTimer;

    void Reset()
    {
        m_uiGlobalTimer = 5000;

        /*if (HasEscortState(STATE_ESCORT_PAUSED) && m_uiPhase == PHASE_FIGHT)
            m_uiPhase = PHASE_COMPLETE;*/

        if (!HasEscortState(STATE_ESCORT_ESCORTING))
        {
            lCreatureList.clear();
            m_uiPhase = 0;
            m_uiPhaseCounter = 0;
        }
    }

    void MoveInLineOfSight(Unit* pWho)
    {
        if (HasEscortState(STATE_ESCORT_ESCORTING) && pWho->GetEntry() == NPC_REETHE && lCreatureList.empty())
            lCreatureList.push_back((Creature*)pWho);

        npc_escortAI::MoveInLineOfSight(pWho);
    }

    void WaypointReached(uint32 uiPointId)
    {
        switch(uiPointId)
        {
            case 9:
                DoScriptText(SAY_OGR_SPOT, me);
                break;
            case 10:
                if (Creature* pReethe = me->FindNearestCreature(NPC_REETHE, 15.0f))
                    DoScriptText(SAY_OGR_RET_WHAT, pReethe);
                break;
            case 11:
                SetEscortPaused(true);
                break;
        }
    }

    void JustSummoned(Creature* pSummoned)
    {
        lCreatureList.push_back(pSummoned);

        pSummoned->setFaction(FACTION_GENERIC_FRIENDLY);

        if (pSummoned->GetEntry() == NPC_CALDWELL)
            pSummoned->GetMotionMaster()->MovePoint(0, m_afMoveTo[0], m_afMoveTo[1], m_afMoveTo[2]);
        else
        {
            if (Creature* pCaldwell = me->FindNearestCreature(NPC_CALDWELL, 15.0f))
            {
                //will this conversion work without compile warning/error?
                size_t iSize = lCreatureList.size();
                pSummoned->GetMotionMaster()->MoveFollow(pCaldwell, 0.5f, (M_PI/2)*(int)iSize);
            }
        }
    }

    void DoStartAttackMe()
    {
        if (!lCreatureList.empty())
        {
            for(std::list<Creature*>::iterator itr = lCreatureList.begin(); itr != lCreatureList.end(); ++itr)
            {
                if ((*itr)->GetEntry() == NPC_REETHE)
                    continue;

                if ((*itr)->isAlive())
                {
                    (*itr)->setFaction(FACTION_THER_HOSTILE);
                    (*itr)->AI()->AttackStart(me);
                }
            }
        }
    }

    void UpdateEscortAI(const uint32 uiDiff)
    {
        if (!UpdateVictim())
        {
            if (HasEscortState(STATE_ESCORT_PAUSED))
            {
                if (m_uiGlobalTimer < uiDiff)
                {
                    m_uiGlobalTimer = 5000;

                    switch(m_uiPhase)
                    {
                        case PHASE_INTRO:
                        {
                            switch(m_uiPhaseCounter)
                            {
                                case 0:
                                    if (Creature* pReethe = me->FindNearestCreature(NPC_REETHE, 15.0f))
                                        DoScriptText(SAY_OGR_RET_SWEAR, pReethe);
                                    break;
                                case 1:
                                    DoScriptText(SAY_OGR_REPLY_RET, me);
                                    break;
                                case 2:
                                    if (Creature* pReethe = me->FindNearestCreature(NPC_REETHE, 15.0f))
                                        DoScriptText(SAY_OGR_RET_TAKEN, pReethe);
                                    break;
                                case 3:
                                    DoScriptText(SAY_OGR_TELL_FIRE, me);
                                    if (Creature* pReethe = me->FindNearestCreature(NPC_REETHE, 15.0f))
                                        DoScriptText(SAY_OGR_RET_NOCLOSER, pReethe);
                                    break;
                                case 4:
                                    if (Creature* pReethe = me->FindNearestCreature(NPC_REETHE, 15.0f))
                                        DoScriptText(SAY_OGR_RET_NOFIRE, pReethe);
                                    break;
                                case 5:
                                    if (Creature* pReethe = me->FindNearestCreature(NPC_REETHE, 15.0f))
                                        DoScriptText(SAY_OGR_RET_HEAR, pReethe);

                                    me->SummonCreature(NPC_CALDWELL, m_afSpawn[0], m_afSpawn[1], m_afSpawn[2], 0.0f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 300000);
                                    me->SummonCreature(NPC_HALLAN, m_afSpawn[0], m_afSpawn[1], m_afSpawn[2], 0.0f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 300000);
                                    me->SummonCreature(NPC_SKIRMISHER, m_afSpawn[0], m_afSpawn[1], m_afSpawn[2], 0.0f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 300000);
                                    me->SummonCreature(NPC_SKIRMISHER, m_afSpawn[0], m_afSpawn[1], m_afSpawn[2], 0.0f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 300000);

                                    m_uiPhase = PHASE_GUESTS;
                                    break;
                            }
                            break;
                        }

                        case PHASE_GUESTS:
                        {
                            switch(m_uiPhaseCounter)
                            {
                                case 6:
                                    if (Creature* pCaldwell = me->FindNearestCreature(NPC_CALDWELL, 15.0f))
                                        DoScriptText(SAY_OGR_CAL_FOUND, pCaldwell);
                                    break;
                                case 7:
                                    if (Creature* pCaldwell = me->FindNearestCreature(NPC_CALDWELL, 15.0f))
                                        DoScriptText(SAY_OGR_CAL_MERCY, pCaldwell);
                                    break;
                                case 8:
                                    if (Creature* pHallan = me->FindNearestCreature(NPC_HALLAN, 15.0f))
                                    {
                                        DoScriptText(SAY_OGR_HALL_GLAD, pHallan);

                                        if (Creature* pReethe = me->FindNearestCreature(NPC_REETHE, 15.0f))
                                            pHallan->CastSpell(pReethe, SPELL_FAKE_SHOT, false);
                                    }
                                    break;
                                case 9:
                                    if (Creature* pReethe = me->FindNearestCreature(NPC_REETHE, 15.0f))
                                    {
                                        DoScriptText(EMOTE_OGR_RET_ARROW, pReethe);
                                        DoScriptText(SAY_OGR_RET_ARROW, pReethe);
                                    }
                                    break;
                                case 10:
                                    if (Creature* pCaldwell = me->FindNearestCreature(NPC_CALDWELL, 15.0f))
                                        DoScriptText(SAY_OGR_CAL_CLEANUP, pCaldwell);

                                    DoScriptText(SAY_OGR_NODIE, me);
                                    break;
                                case 11:
                                    DoStartAttackMe();
                                    m_uiPhase = PHASE_COMPLETE;
                                    break;
                            }
                            break;
                        }

                        case PHASE_COMPLETE:
                        {
                            switch(m_uiPhaseCounter)
                            {
                                case 12:
                                    if (Player* pPlayer = GetPlayerForEscort())
                                        pPlayer->GroupEventHappens(QUEST_QUESTIONING, me);
                                    DoScriptText(SAY_OGR_SURVIVE, me);
                                    break;
                                case 13:
                                    if (Creature* pReethe = me->FindNearestCreature(NPC_REETHE, 15.0f))
                                        DoScriptText(SAY_OGR_RET_LUCKY, pReethe);
                                    break;
                                case 14:
                                    if (Creature* pReethe = me->FindNearestCreature(NPC_REETHE, 15.0f))
                                        pReethe->setDeathState(JUST_DIED);
                                    break;
                                case 15:
                                    DoScriptText(SAY_OGR_THANKS, me);
                                    SetRun(true);
                                    SetEscortPaused(false);
                                    break;
                            }
                            break;
                        }
                    }
                        ++m_uiPhaseCounter;
                }
                else
                    m_uiGlobalTimer -= uiDiff;
            }

            return;
        }

        DoMeleeAttackIfReady();
    }
};

bool QuestAccept_npc_ogron(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_QUESTIONING)
    {
        pCreature->setFaction(FACTION_ESCORT_N_FRIEND_PASSIVE);
        DoScriptText(SAY_OGR_START, pCreature, pPlayer);

        if (npc_ogronAI* pEscortAI = CAST_AI(npc_ogronAI, (pCreature->AI())))
            pEscortAI->Start(false, false, pPlayer->GetGUID(), pQuest, true);
    }

    return true;
}

CreatureAI* GetAI_npc_ogron(Creature* pCreature)
{
    return new npc_ogronAI(pCreature);
}

/*######
## npc_private_hendel
######*/

enum eHendel
{
    SAY_PROGRESS_1_TER          = -1000411,
    SAY_PROGRESS_2_HEN          = -1000412,
    SAY_PROGRESS_3_TER          = -1000413,
    SAY_PROGRESS_4_TER          = -1000414,
    EMOTE_SURRENDER             = -1000415,

    QUEST_MISSING_DIPLO_PT16    = 1324,
    FACTION_HOSTILE             = 168,

    NPC_SENTRY                  = 5184,
    NPC_JAINA                   = 4968,
    NPC_TERVOSH                 = 4967,
    NPC_PAINED                  = 4965,

    PHASE_ATTACK                = 1,
    PHASE_COMPLETED             = 2
};

struct EventLocation
{
    float m_fX, m_fY, m_fZ;
};

EventLocation m_afEventMoveTo[] =
{
    {-2943.92f, -3319.41f, 29.8336f},
    {-2933.01f, -3321.05f, 29.5781f}

};

struct npc_private_hendelAI : public ScriptedAI
{
    npc_private_hendelAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    std::list<Creature*> lCreatureList;

    uint32 m_uiPhaseCounter;
    uint32 m_uiEventTimer;
    uint32 m_uiPhase;
    uint64 PlayerGUID;

    void Reset()
    {
        PlayerGUID = 0;
        m_uiPhase = 0;
        m_uiEventTimer = 0;
        m_uiPhaseCounter = 0;
        lCreatureList.clear();
    }
    
    void AttackedBy(Unit* pAttacker)
    {
        if (me->getVictim())
            return;

        if (me->IsFriendlyTo(pAttacker))
            return;

        AttackStart(pAttacker);
    }

    void JustSummoned(Creature* pSummoned)
    {
        pSummoned->RemoveUnitMovementFlag(MOVEFLAG_WALK_MODE);

        if (pSummoned->GetEntry() == NPC_TERVOSH)
        {
            pSummoned->GetMotionMaster()->MovePoint(0, -2889.48f, -3349.37f, 32.0619f);
            return;
        }
        if (pSummoned->GetEntry() == NPC_JAINA)
        {
            pSummoned->GetMotionMaster()->MovePoint(0, -2889.27f, -3347.17f, 32.2615f);
            return;
        }
        pSummoned->GetMotionMaster()->MovePoint(0, -2890.31f,-3345.23f,32.3087f);
    }

    void DoAttackPlayer()
    {
        Player* pPlayer = Unit::GetPlayer(*me, PlayerGUID);
        if(!pPlayer)
            return;

        me->setFaction(FACTION_HOSTILE);
        me->AI()->AttackStart(pPlayer);

        float x, y, z;

        me->GetPosition(x, y, z);
        CellPair pair(Oregon::ComputeCellPair(x, y));
        Cell cell(pair);
        cell.data.Part.reserved = ALL_DISTRICT;
        cell.SetNoCreate();

        Oregon::AllCreaturesOfEntryInRange check(me, NPC_SENTRY, 20);
        Oregon::CreatureListSearcher<Oregon::AllCreaturesOfEntryInRange> searcher(lCreatureList, check);
        TypeContainerVisitor<Oregon::CreatureListSearcher<Oregon::AllCreaturesOfEntryInRange>, GridTypeMapContainer> cSearcher(searcher);
        cell.Visit(pair, cSearcher, *(me->GetMap()));

        if (!lCreatureList.empty())
        {
            for(std::list<Creature*>::iterator itr = lCreatureList.begin(); itr != lCreatureList.end(); ++itr)
            {
                if ((*itr)->isAlive())
                {
                    (*itr)->setFaction(FACTION_HOSTILE);
                    (*itr)->AI()->AttackStart(pPlayer);
                }
            }
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!UpdateVictim() && m_uiPhase)
        {
            switch(m_uiPhase)
            {
            case PHASE_ATTACK:
                DoAttackPlayer();
                break;

            case PHASE_COMPLETE:
                if (m_uiEventTimer <= uiDiff)
                {
                    m_uiEventTimer = 5000;

                    switch (m_uiPhaseCounter)
                    {
                    case 0:
                        DoScriptText(EMOTE_SURRENDER, me);
                        break;
                    case 1:
                        if (Creature* pTervosh = me->FindNearestCreature(NPC_TERVOSH, 10.0f))
                            DoScriptText(SAY_PROGRESS_1_TER, pTervosh);
                        break;
                    case 2:
                        DoScriptText(SAY_PROGRESS_2_HEN, me);
                        break;
                    case 3:
                        if (Creature* pTervosh = me->FindNearestCreature(NPC_TERVOSH, 10.0f))
                            DoScriptText(SAY_PROGRESS_3_TER, pTervosh);
                        break;
                    case 4:
                        if (Creature* pTervosh = me->FindNearestCreature(NPC_TERVOSH, 10.0f))
                                DoScriptText(SAY_PROGRESS_4_TER, pTervosh);
                        if (Player* pPlayer = Unit::GetPlayer(*me, PlayerGUID))
                            pPlayer->GroupEventHappens(QUEST_MISSING_DIPLO_PT16, me);
                        Reset();
                        break;
                    }
                    ++m_uiPhaseCounter;
                }
                else
                    m_uiEventTimer -= uiDiff;
            }
        }
        return;
    }
    
    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    {
        if (uiDamage > me->GetHealth() || ((me->GetHealth() - uiDamage)*100 / me->GetMaxHealth() < 20))
        {
            uiDamage = 0;
            m_uiPhase = PHASE_COMPLETE;
            m_uiEventTimer = 2000;

            me->RestoreFaction();
            me->RemoveAllAuras();
            me->DeleteThreatList();
            me->CombatStop(true);
            me->RemoveUnitMovementFlag(MOVEFLAG_WALK_MODE);
            me->SetHomePosition(-2892.28f,-3347.81f,31.8609f,0.160719f);
            me->GetMotionMaster()->MoveTargetedHome();

            if (Player* pPlayer = Unit::GetPlayer(*me, PlayerGUID))
                pPlayer->CombatStop(true);

            if (!lCreatureList.empty())
            {
                uint16 N = -1;

                for(std::list<Creature*>::iterator itr = lCreatureList.begin(); itr != lCreatureList.end(); ++itr)
                {
                    if ((*itr)->isAlive())
                    {
                        N = N + 1;
                        (*itr)->RestoreFaction();
                        (*itr)->RemoveAllAuras();
                        (*itr)->DeleteThreatList();
                        (*itr)->CombatStop(true);
                        (*itr)->RemoveUnitMovementFlag(MOVEFLAG_WALK_MODE);
                        (*itr)->GetMotionMaster()->MovePoint(0, m_afEventMoveTo[N].m_fX,  m_afEventMoveTo[N].m_fY,  m_afEventMoveTo[N].m_fZ);
                        (*itr)->ForcedDespawn(5000);
                    }
                }
            }
            lCreatureList.clear();

            me->ForcedDespawn(60000);
            me->SummonCreature(NPC_TERVOSH, -2876.66f, -3346.96f, 35.6029f, 0.0f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000);
            me->SummonCreature(NPC_JAINA, -2876.95f, -3342.78f, 35.6244f, 0.0f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000);
            me->SummonCreature(NPC_PAINED, -2877.67f, -3338.63f, 35.2548f, 0.0f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000);       
        }
    }
};

bool QuestAccept_npc_private_hendel(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_MISSING_DIPLO_PT16)
    {
        CAST_AI(npc_private_hendelAI, pCreature->AI())->m_uiPhase = PHASE_ATTACK;
        CAST_AI(npc_private_hendelAI, pCreature->AI())->PlayerGUID = pPlayer->GetGUID();
    }

    return true; 
}

CreatureAI* GetAI_npc_private_hendel(Creature* pCreature)
{
    return new npc_private_hendelAI(pCreature);
}

void AddSC_dustwallow_marsh()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "mobs_risen_husk_spirit";
    newscript->GetAI = &GetAI_mobs_risen_husk_spirit;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_restless_apparition";
    newscript->pGossipHello =   &GossipHello_npc_restless_apparition;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_deserter_agitator";
    newscript->GetAI = &GetAI_npc_deserter_agitator;
    newscript->pGossipHello = &GossipHello_npc_deserter_agitator;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_lady_jaina_proudmoore";
    newscript->pGossipHello = &GossipHello_npc_lady_jaina_proudmoore;
    newscript->pGossipSelect = &GossipSelect_npc_lady_jaina_proudmoore;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_nat_pagle";
    newscript->pGossipHello = &GossipHello_npc_nat_pagle;
    newscript->pGossipSelect = &GossipSelect_npc_nat_pagle;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_morokk";
    newscript->GetAI = &GetAI_npc_morokk;
    newscript->pQuestAccept = &QuestAccept_npc_morokk;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_ogron";
    newscript->GetAI = &GetAI_npc_ogron;
    newscript->pQuestAccept = &QuestAccept_npc_ogron;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_private_hendel";
    newscript->GetAI = &GetAI_npc_private_hendel;
    newscript->pQuestAccept = &QuestAccept_npc_private_hendel;
    newscript->RegisterSelf();
}

