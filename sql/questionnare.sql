--source /home/jerry/Desktop/questionnare/sql/questionnare.sql
CREATE DATABASE IF NOT EXISTS survey_system;
USE survey_system;

-- 创建用户表（Users）
CREATE TABLE Users (
    user_id INT AUTO_INCREMENT PRIMARY KEY,
    user_name VARCHAR(255) UNIQUE NOT NULL,
    password VARCHAR(255) NOT NULL,
    is_root TINYINT(1) DEFAULT 0
);

-- 创建问卷表（Surveys）
CREATE TABLE Surveys (
    survey_id INT AUTO_INCREMENT PRIMARY KEY,
    title VARCHAR(255) NOT NULL,
    user_id INT NOT NULL,  -- 添加隶属用户ID
    is_filled TINYINT(1) DEFAULT 0,
    root_survey_id INT,  --隶属的root问卷
    FOREIGN KEY (user_id) REFERENCES Users(id) ON DELETE CASCADE  -- 关联用户表
);

-- 创建题目表（Questions）
CREATE TABLE Questions (
    question_id INT AUTO_INCREMENT PRIMARY KEY,
    survey_id INT,
    question_text TEXT NOT NULL,
    question_type ENUM('single_choice', 'multiple_choice', 'fill_in_blank') NOT NULL,
    FOREIGN KEY (survey_id) REFERENCES Surveys(survey_id) ON DELETE CASCADE
    root_question_id INT, 
);

-- 创建选项表（Options）
CREATE TABLE Options (
    option_id INT AUTO_INCREMENT PRIMARY KEY,
    question_id INT,
    option_text VARCHAR(255) NOT NULL,
    FOREIGN KEY (question_id) REFERENCES Questions(question_id) ON DELETE CASCADE
    root_option_id INT,
);

-- 创建回答表（Responses）
CREATE TABLE Responses (
    response_id INT AUTO_INCREMENT PRIMARY KEY,
    survey_id INT,
    question_id INT,
    user_id INT,
    answer TEXT,
    FOREIGN KEY (survey_id) REFERENCES Surveys(survey_id) ON DELETE CASCADE,
    FOREIGN KEY (question_id) REFERENCES Questions(question_id) ON DELETE CASCADE
);



