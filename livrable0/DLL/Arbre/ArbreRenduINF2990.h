///////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990.h
/// @author Martin Bisson
/// @date 2007-03-23
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_ARBRERENDUINF2990_H__
#define __ARBRE_ARBRERENDUINF2990_H__


#include "ArbreRendu.h"
#include "noeudAbstrait.h"

#include <map>
#include <string>


///////////////////////////////////////////////////////////////////////////
/// @class ArbreRenduINF2990
/// @brief Classe qui repr�sente l'arbre de rendu sp�cifique au projet de
///        INF2990.
///
///        Cette classe s'occupe de configurer les usines des noeuds qui
///        seront utilis�s par le projet.
///
/// @author Martin Bisson
/// @date 2007-03-23
///////////////////////////////////////////////////////////////////////////
class ArbreRenduINF2990 : public ArbreRendu
{
public:
   /// Constructeur par d�faut.
   ArbreRenduINF2990();
   /// Destructeur.
   virtual ~ArbreRenduINF2990();

   /// Initialise l'arbre de rendu � son �tat initial.
   void initialiser();


	/// La cha�ne repr�sentant le type des araign�es.
   static const std::string NOM_ARAIGNEE;
	/// La cha�ne repr�sentant le type des cones-cubes.
   static const std::string NOM_CONECUBE;

   static const std::string NOM_PALETTE_JOUEUR1;
   static const std::string NOM_PALETTE_JOUEUR2;
   static const std::string NOM_PLAQUE;
   static const std::string NOM_BUTOIR_TRIANGULAIRE;
   static const std::string NOM_BUTOIR_CIRCULAIRE;
   static const std::string NOM_CIBLE;
   static const std::string NOM_RESSORT;
   static const std::string NOM_GENERATEUR_BILLE;
   static const std::string NOM_TROU;
   static const std::string NOM_PORTAIL;
   static const std::string NOM_MUR;
};


#endif // __ARBRE_ARBRERENDUINF2990_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
