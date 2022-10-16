-- -----------------------------------------------------------------
-- Creation Script: Code.Dash
-- Table Count: 4
-- Created: 2022-09-18 20:31
-- -----------------------------------------------------------------

-- Recreate schema in the database
DROP SCHEMA IF EXISTS code_dash_test;
CREATE SCHEMA code_dash_test;
USE code_dash_test;

-- Create a table of the problem types
CREATE TABLE IF NOT EXISTS `problem`
(
    `id` INT AUTO_INCREMENT PRIMARY KEY,
    `created` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP(),
    `code` VARCHAR(50) NOT NULL UNIQUE,
    `name` VARCHAR(200) NOT NULL,
    `details` VARCHAR(500) NOT NULL,
    `training_file` VARCHAR(100) NOT NULL
);

-- Create a table of the algorithm types
CREATE TABLE IF NOT EXISTS `algorithm`
(
    `id` INT AUTO_INCREMENT PRIMARY KEY,
    `created` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP(),
    `code` VARCHAR(50) NOT NULL UNIQUE,
    `name` VARCHAR(200) NOT NULL,
    `details` VARCHAR(500) NOT NULL,
    `version` VARCHAR(20) NOT NULL
);

-- Create a table of the status codes
CREATE TABLE IF NOT EXISTS `status`
(
    `id` INT AUTO_INCREMENT PRIMARY KEY,
    `created` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP(),
    `code` VARCHAR(50) NOT NULL UNIQUE,
    `name` VARCHAR(200) NOT NULL,
    `notes` VARCHAR(500) NOT NULL
);

-- Create a table of the status codes
CREATE TABLE IF NOT EXISTS `score`
(
    `id` INT AUTO_INCREMENT PRIMARY KEY,
    `created` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP(),
    `session_id` INT NOT NULL,
    `epoch` INT NOT NULL,
    `score` FLOAT NOT NULL
);

-- Create table for site details
CREATE TABLE IF NOT EXISTS `site_details`
(
    `id` INT AUTO_INCREMENT PRIMARY KEY,
    `key` VARCHAR(200) UNIQUE NOT NULL,
    `value` VARCHAR(500)
);

INSERT INTO `site_details`(`key`,`value`) VALUES ('site_name','code.dash');
INSERT INTO `site_details`(`key`,`value`) VALUES ('description','A dashboard for monitoring code generation');
INSERT INTO `site_details`(`key`,`value`) VALUES ('author','Wild Boar');
INSERT INTO `site_details`(`key`,`value`) VALUES ('email','trevorgeek@gmail.com');
INSERT INTO `site_details`(`key`,`value`) VALUES ('upload_folder','/home/trevor/uploads');
INSERT INTO `site_details`(`key`,`value`) VALUES ('upload_url_folder','../uploads');
INSERT INTO `site_details`(`key`,`value`) VALUES ('module_folder','/home/trevor/Modules');

-- Create a table to hold the information associated with a session
CREATE TABLE IF NOT EXISTS `session`
(
    `id` INT AUTO_INCREMENT PRIMARY KEY,
    `created` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP(),
    `start` DATETIME,
    `end` DATETIME,
    `algorithm_id` INT,
    `problem_id` INT,
    `status_id` INT,
    `message` VARCHAR(500),
    `epoch` INT,
    `best_score` FLOAT,
    `best_solution` VARCHAR(2000),
    `focus` INT NOT NULL
);

ALTER TABLE `session` ADD FOREIGN KEY (`algorithm_id`) REFERENCES `algorithm`(`id`);
ALTER TABLE `session` ADD FOREIGN KEY (`problem_id`) REFERENCES `problem`(`id`);
ALTER TABLE `session` ADD FOREIGN KEY (`status_id`) REFERENCES `status`(`id`);

-- Create a table of the status codes
CREATE TABLE IF NOT EXISTS `score`
(
    `id` INT AUTO_INCREMENT PRIMARY KEY,
    `created` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP(),
    `session_id` INT NOT NULL,
    `epoch` INT NOT NULL,
    `score` FLOAT NOT NULL
);

ALTER TABLE `score` ADD FOREIGN KEY (`session_id`) REFERENCES `session`(`id`);

-- Create a table of the status codes
CREATE TABLE IF NOT EXISTS `meta`
(
    `id` INT AUTO_INCREMENT PRIMARY KEY,
    `parameter` VARCHAR(100)  UNIQUE NOT NULL,
    `value` VARCHAR(500) NOT NULL
);

INSERT INTO `meta`(`parameter`, `value`) VALUES ('SITE_LOCATION', '/home/trevor/Work/Research/Trevor/Code.Gen/Source/Code.Dash/build/Code.Dash');