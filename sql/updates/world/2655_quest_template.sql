-- Drop ReqSourceRef fields
ALTER TABLE quest_template
  DROP COLUMN ReqSourceRef1,
  DROP COLUMN ReqSourceRef2,
  DROP COLUMN ReqSourceRef3,
  DROP COLUMN ReqSourceRef4;

-- all quests that use RequiredSpellCastX fields
UPDATE `quest_template` SET `SpecialFlags`=`SpecialFlags`|32 WHERE `entry` IN
(28,29,532,553,849,877,905,974,2118,2932,2994,3825,5096,5163,5165,5441,
6124,6129,6381,6395,6661,8346,8889,9066,9169,9193,9275,9294,9391,9440,
9444,9447,9489,9526,9600,9629,9667,9685,9720,9805,9824,9874,9910,10011,
10078,10087,10129,10144,10146,10182,10208,10233,10240,10305,10306,10307,
10313,10335,10345,10392,10426,10446,10447,10488,10545,10564,10598,10637,
10688,10714,10771,10792,10802,10808,10813,10833,10859,10866,10895,10913,
10923,10935,11055,11150,11205,11232,11245,11247,11258,11259,11285,11330,
11332,11421,11496,11515,11523,11542,11543,11547,11568,11576,11582,11610,
11617,11637,11656,11677,11684,11694,11713,11880,12092,12094,12096,12154,
12172,12173,12180,12213,12232,12267,12417,12449,12502,12588,12591,12598,
12641,12669,12728,12859,13110,13119,13211);