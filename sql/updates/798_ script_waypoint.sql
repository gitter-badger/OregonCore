SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for `script_waypoint`
-- ----------------------------
DROP TABLE IF EXISTS `script_waypoint`;
CREATE TABLE `script_waypoint` (
  `entry` mediumint(8) unsigned NOT NULL DEFAULT '0' COMMENT 'creature_template entry',
  `pointid` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `location_x` float NOT NULL DEFAULT '0',
  `location_y` float NOT NULL DEFAULT '0',
  `location_z` float NOT NULL DEFAULT '0',
  `waittime` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'waittime in millisecs',
  `point_comment` text,
  PRIMARY KEY (`entry`,`pointid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED COMMENT='Script Creature waypoints';

-- ----------------------------
-- Records of script_waypoint
-- ----------------------------
DELETE FROM script_waypoint WHERE entry = '7784';
INSERT INTO `script_waypoint` VALUES ('7784', '83', '-6957.16', '-4788.92', '6.26', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '82', '-6970.41', '-4788.77', '9.42', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '81', '-6984.95', '-4788.61', '9.3', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '80', '-7001.71', '-4769.73', '10.59', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '79', '-7013.9', '-4758.64', '10.28', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '78', '-7035.12', '-4754.39', '9.19', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '77', '-7061.81', '-4751.98', '9.26', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '76', '-7082.79', '-4752.99', '9.97', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '75', '-7101.06', '-4753.87', '8.92', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '74', '-7122.6', '-4754.91', '9.66', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '73', '-7139.58', '-4756.02', '9.53', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '72', '-7159.61', '-4752.9', '9.52', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '71', '-7182.01', '-4749.41', '9.09', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '70', '-7201.86', '-4746.32', '9.58', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '69', '-7217.52', '-4743.87', '10.79', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '68', '-7236.7', '-4742.24', '10.16', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '67', '-7258.33', '-4742.93', '9.64', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '66', '-7281', '-4743.66', '11.21', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '65', '-7302.35', '-4744.35', '11.97', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '64', '-7321.62', '-4744.97', '11.58', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '63', '-7341', '-4752.11', '10.17', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '62', '-7367.25', '-4764.17', '11.92', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '61', '-7393.84', '-4770.19', '12.57', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '60', '-7426.27', '-4777.83', '9.54', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '59', '-7453.18', '-4782.41', '9.15', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '58', '-7469.1', '-4785.11', '10.42', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '57', '-7490.79', '-4788.8', '10.53', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '56', '-7512.07', '-4793.5', '9.35', '0', 'Wastewander');
INSERT INTO `script_waypoint` VALUES ('7784', '55', '-7536.4', '-4789.32', '8.92', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '54', '-7558.51', '-4779.01', '9.64', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '53', '-7579.43', '-4767.07', '8.93', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '52', '-7603.15', '-4757.53', '9.06', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '51', '-7620.08', '-4753.96', '8.93', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '50', '-7641.47', '-4750.33', '8.94', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '49', '-7665.33', '-4752.62', '10.56', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '48', '-7697.98', '-4763.8', '9.52', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '47', '-7724.11', '-4772.75', '10.28', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '46', '-7746.42', '-4780.39', '9.84', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '45', '-7778.68', '-4738.05', '8.89', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '44', '-7793.88', '-4717.55', '10.48', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '43', '-7807.86', '-4698.69', '11.24', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '42', '-7826.17', '-4673.99', '10.61', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '41', '-7840.79', '-4654.26', '9.45', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '40', '-7862.83', '-4624.53', '10.21', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '39', '-7883.33', '-4593.91', '12.15', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '38', '-7904.09', '-4566.67', '12.59', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '37', '-7932.45', '-4528.91', '10.08', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '36', '-7958.83', '-4503.98', '9.69', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '35', '-7981.64', '-4482.44', '10.32', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '34', '-8015.39', '-4454.33', '9.39', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '33', '-8032.15', '-4443.47', '9.97', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '32', '-8063.15', '-4423.4', '10.07', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '31', '-8104.86', '-4399.03', '8.93', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '30', '-8129.25', '-4394.57', '10.92', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '29', '-8155.65', '-4397.74', '8.99', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '28', '-8193.31', '-4406.04', '10.17', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '27', '-8224.76', '-4419.39', '13.03', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '26', '-8272.2', '-4433.31', '9.6', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '25', '-8303.78', '-4441.96', '11.89', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '24', '-8336.4', '-4446.39', '8.98', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '23', '-8353.96', '-4448.79', '10.1', '0', 'Scorpid');
INSERT INTO `script_waypoint` VALUES ('7784', '22', '-8371.24', '-4446.13', '9.47', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '21', '-8403.41', '-4441.16', '11.83', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '20', '-8441.36', '-4435.31', '9.4', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '19', '-8471.91', '-4430.6', '9.56', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '18', '-8503.48', '-4423.7', '13.59', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '17', '-8536.45', '-4416.49', '11.84', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '16', '-8560.33', '-4411.27', '13.17', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '15', '-8614.73', '-4398.6', '9.86', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '14', '-8645.19', '-4388.62', '12.56', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '13', '-8668.76', '-4380.38', '11.69', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '12', '-8688.27', '-4372.85', '13.64', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '11', '-8706.77', '-4346.14', '16.12', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '10', '-8724.13', '-4353.55', '20.72', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '9', '-8745.49', '-4363.16', '22.8', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '8', '-8764.97', '-4366.94', '25.23', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '7', '-8786.68', '-4366.18', '23.91', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '6', '-8803.37', '-4369.68', '30.06', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '5', '-8818.88', '-4372.75', '36.43', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '4', '-8825.1', '-4373.56', '41.44', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '3', '-8829.21', '-4373.72', '44.14', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '2', '-8832.93', '-4373.85', '45.67', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '1', '-8834.68', '-4373.88', '45.71', '0', '');
INSERT INTO `script_waypoint` VALUES ('7784', '0', '-8843.73', '-4374.44', '43.71', '0', '');
DELETE FROM script_waypoint WHERE entry = '20129';
INSERT INTO `script_waypoint` VALUES ('20129', '25', '-8375.42', '-4250.41', '-205.14', '5000', '');
INSERT INTO `script_waypoint` VALUES ('20129', '24', '-8375.42', '-4250.41', '-205.14', '5000', '');
INSERT INTO `script_waypoint` VALUES ('20129', '23', '-8304.54', '-4357.2', '-208.2', '2000', '');
INSERT INTO `script_waypoint` VALUES ('20129', '22', '-8304.54', '-4357.2', '-208.2', '18000', '');
INSERT INTO `script_waypoint` VALUES ('20129', '21', '-8364.83', '-4393.32', '-205.91', '0', '');
INSERT INTO `script_waypoint` VALUES ('20129', '20', '-8427.54', '-4426', '-211.13', '0', '');
INSERT INTO `script_waypoint` VALUES ('20129', '19', '-8468.72', '-4437.67', '-215.45', '0', '');
INSERT INTO `script_waypoint` VALUES ('20129', '18', '-8649.06', '-4394.36', '-208.46', '2000', '');
INSERT INTO `script_waypoint` VALUES ('20129', '17', '-8649.06', '-4394.36', '-208.46', '18000', '');
INSERT INTO `script_waypoint` VALUES ('20129', '16', '-8649.06', '-4394.36', '-208.46', '6000', '');
INSERT INTO `script_waypoint` VALUES ('20129', '15', '-8642.81', '-4304.37', '-209.57', '0', '');
INSERT INTO `script_waypoint` VALUES ('20129', '14', '-8703.71', '-4234.58', '-209.5', '2000', '');
INSERT INTO `script_waypoint` VALUES ('20129', '13', '-8703.71', '-4234.58', '-209.5', '14000', '');
INSERT INTO `script_waypoint` VALUES ('20129', '12', '-8667.76', '-4252.13', '-209.56', '0', '');
INSERT INTO `script_waypoint` VALUES ('20129', '11', '-8467.26', '-4198.63', '-214.21', '0', '');
INSERT INTO `script_waypoint` VALUES ('20129', '10', '-8437.82', '-4120.84', '-208.59', '2000', '');
INSERT INTO `script_waypoint` VALUES ('20129', '9', '-8437.82', '-4120.84', '-208.59', '15000', '');
INSERT INTO `script_waypoint` VALUES ('20129', '8', '-8437.82', '-4120.84', '-208.59', '18000', '');
INSERT INTO `script_waypoint` VALUES ('20129', '7', '-8437.82', '-4120.84', '-208.59', '13000', '');
INSERT INTO `script_waypoint` VALUES ('20129', '6', '-8437.82', '-4120.84', '-208.59', '16000', '');
INSERT INTO `script_waypoint` VALUES ('20129', '5', '-8437.82', '-4120.84', '-208.59', '10000', '');
INSERT INTO `script_waypoint` VALUES ('20129', '4', '-8439.4', '-4180.05', '-209.25', '0', '');
INSERT INTO `script_waypoint` VALUES ('20129', '3', '-8374.93', '-4250.21', '-204.38', '2000', '');
INSERT INTO `script_waypoint` VALUES ('20129', '2', '-8374.93', '-4250.21', '-204.38', '10000', '');
INSERT INTO `script_waypoint` VALUES ('20129', '1', '-8374.93', '-4250.21', '-204.38', '16000', '');
INSERT INTO `script_waypoint` VALUES ('20129', '0', '-8374.93', '-4250.21', '-204.38', '5000', '');
