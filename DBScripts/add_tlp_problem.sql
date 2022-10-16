-- -----------------------------------------------------------------
-- Insert Script: Add values to the Status table
--
-- Created: 2022-09-18 20:31
-- Author: @wildboar
-- -----------------------------------------------------------------

USE code_dash;

-- -----------------------------------------------------------------
-- Insert problem into the main database
-- -----------------------------------------------------------------
INSERT INTO `problem`(`code`,`name`,`details`,`training_file`) 
VALUES ("TLP_0000", "Top Left Finder", "Given four points in 2D space, return the index of the top left point.", "training/tlp_0000.txt");

USE code_dash_test;

-- -----------------------------------------------------------------
-- Insert the problem into the testing database
-- -----------------------------------------------------------------
INSERT INTO `problem`(`code`,`name`,`details`,`training_file`) 
VALUES ("TLP_0000", "Top Left Finder", "Given four points in 2D space, return the index of the top left point.", "training/tlp_0000.txt");