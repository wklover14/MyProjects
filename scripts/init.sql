--CREATE OR REPLACE FUNCTION change_owner_to_user1() RETURNS void AS $$
--DECLARE
--    r RECORD;
--BEGIN
--    FOR r IN (SELECT tablename FROM pg_tables WHERE schemaname = 'public') LOOP
--        EXECUTE 'ALTER TABLE ' || r.tablename || ' OWNER TO gabby';
--    END LOOP;
--END;
--$$ LANGUAGE plpgsql;

--DELETE ALL TABLES

DO $$ DECLARE
    r RECORD;
BEGIN
    FOR r IN (SELECT tablename FROM pg_tables WHERE schemaname = current_schema()) LOOP
        EXECUTE 'DROP TABLE IF EXISTS ' || r.tablename || ' CASCADE';
    END LOOP;
END $$;


-- Delete database projectManager

DROP DATABASE IF EXISTS projectManager CASCADE;
CREATE DATABASE projectManager ; 

-- Create user Gabby
-- Delete this user if already exists

DO $code$
BEGIN
	IF EXISTS (SELECT  FROM pg_catalog.pg_roles WHERE rolname  = 'gabby')
	THEN
		REVOKE CREATE ON DATABASE postgres FROM DATABASE;
		DROP USER gabby;
	END IF;
END
$code$;

CREATE USER gabby WITH PASSWORD 'gabby' ;
GRANT CREATE ON DATABASE postgres TO gabby ;
