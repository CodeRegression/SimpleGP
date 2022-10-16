-- -----------------------------------------------------------------
-- Insert Script: Add values to the Status table
--
-- Created: 2022-09-18 20:31
-- Author: @wildboar
-- -----------------------------------------------------------------

USE code_dash_test;

-- -----------------------------------------------------------------
-- Insert values here
-- -----------------------------------------------------------------
INSERT INTO `status`(`code`,`name`,`notes`) VALUES ("CREATE", "CREATED", "The session has been created, but not run yet.");
INSERT INTO `status`(`code`,`name`,`notes`) VALUES ("START", "STARTED", "The session is running.");
INSERT INTO `status`(`code`,`name`,`notes`) VALUES ("STOP", "PAUSED", "The session has started, but currently is not running.");
INSERT INTO `status`(`code`,`name`,`notes`) VALUES ("END", "FINISHED", "The session has completed with success.");
INSERT INTO `status`(`code`,`name`,`notes`) VALUES ("FAIL", "FAILED", "A failure has occurred during the session.");
