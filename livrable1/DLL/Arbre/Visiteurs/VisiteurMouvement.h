///////////////////////////////////////////////////////////////////////////
/// @file VisiteurMouvement.h
/// @author Tommy Sagala
/// @date 2014-10-03
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __Visiteur_MOUVEMENT_H__
#define __Visiteur_MOUVEMENT_H__

#include "VisiteurAbstrait.h"
#include <vector>


class VisiteurMouvement : public VisiteurAbstrait
{
public:
	virtual void revert() =0;
	virtual void visiteAll(glm::dvec3 mouvement) =0;
	std::string getType() { return type_; }
protected:
	glm::dvec3 mouvementTotal_;
	glm::dvec3 mouvement_;
	std::vector<NoeudAbstrait*> noeudsSelectionnes_;
	std::string type_;
};

#endif