#ifndef A_PROJECT_DB_H
#define A_PROJECT_DB_H

#include "logic/a_project.h"
#include "database/connexion_db.h"

class a_project_db
{
public:
    a_project_db();
    ~a_project_db() ;
    void insert(const A_project&, int ) const ;
    void remove(const A_project& ) const ;
    void remove(int id_project) const ;
    void update(const A_project& ) const ;
    bool is_present(const A_project& ) const ;
};

#endif // A_PROJECT_DB_H
