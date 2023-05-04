-- CREATE ALL THE TABLE

DROP TABLE IF  EXISTS Manager CASCADE;
DROP TABLE IF  EXISTS Category CASCADE;
DROP TABLE IF  EXISTS Document CASCADE;
DROP TABLE IF  EXISTS a_project CASCADE;
DROP TABLE IF  EXISTS Project_value CASCADE;
DROP TABLE IF  EXISTS Project_step CASCADE;
DROP TABLE IF  EXISTS Project_step_value CASCADE;
DROP TABLE IF  EXISTS Step CASCADE;
DROP TABLE IF  EXISTS Checkpoint CASCADE;
DROP TABLE IF  EXISTS Task CASCADE;


------------------------------------------------------------
-- Table: Manager
------------------------------------------------------------

CREATE TABLE Manager (
id_manager INTEGER PRIMARY KEY,
name VARCHAR (50),
password VARCHAR (50)
);

------------------------------------------------------------
-- Table: Category
------------------------------------------------------------

CREATE TABLE Category (
id_category INTEGER PRIMARY KEY,
id_manager INTEGER REFERENCES Manager(id_manager), 
name VARCHAR (50),
color varchar(50)
);

------------------------------------------------------------
-- Table: a_project
------------------------------------------------------------

CREATE TABLE a_project (
id_project INTEGER PRIMARY KEY,
id_category INTEGER NOT NULL,
name VARCHAR (30),
begin_date DATE,
end_date DATE,
comment VARCHAR (300),
description VARCHAR (150),
priority INTEGER,
FOREIGN KEY (id_category) REFERENCES Category(id_category)
);

------------------------------------------------------------
-- Table: Project_value
------------------------------------------------------------

CREATE TABLE Project_value (
id_project_value INTEGER PRIMARY KEY,
id_project INTEGER REFERENCES a_project(id_project),
status INTEGER ,
total_value INTEGER,
CHECK (status = 0),
CHECK (total_value = 100)
);

------------------------------------------------------------
-- Table: Project_step
------------------------------------------------------------

CREATE TABLE Project_step (
id_project_step INTEGER PRIMARY KEY,
id_project INTEGER REFERENCES a_project(id_project),
message VARCHAR (50)
);

------------------------------------------------------------
-- Table: Project_step_value
------------------------------------------------------------

CREATE TABLE Project_step_value (
id_project_step_value INTEGER PRIMARY KEY,
id_project_step INTEGER REFERENCES Project_step (id_project_step),
message VARCHAR (50)
);

------------------------------------------------------------
-- Table: Document
------------------------------------------------------------

CREATE TABLE Document (
id_ap INTEGER ,
id_doc INTEGER PRIMARY KEY,
name VARCHAR (50),
link VARCHAR (50),
FOREIGN KEY (id_ap) REFERENCES a_project (id_project)
);


------------------------------------------------------------
-- Table: Step
------------------------------------------------------------

CREATE TABLE Step (
id_step INTEGER PRIMARY KEY,
id_project_step INTEGER,
date DATE,
is_done BOOLEAN,
comment VARCHAR (50),
FOREIGN KEY (id_project_step) REFERENCES Project_step(id_project_step)
);

------------------------------------------------------------
-- Table: Checkpoint
------------------------------------------------------------

CREATE TABLE Checkpoint (
id_checkpoint INTEGER,
id_psv INTEGER,
date DATE,
is_done BOOLEAN,
comment VARCHAR (50),
value INTEGER ,
PRIMARY KEY ( id_checkpoint, id_psv),
FOREIGN KEY (id_psv) REFERENCES Project_step_value ( id_project_step_value )
);

------------------------------------------------------------
-- Table: Task
------------------------------------------------------------

CREATE TABLE Task (
id_task INTEGER,
id_manager INTEGER,
name VARCHAR (50),
is_done BOOLEAN,
delay DATE,
PRIMARY KEY ( id_task, id_manager ),
FOREIGN KEY (id_manager) REFERENCES Manager( id_manager)
);