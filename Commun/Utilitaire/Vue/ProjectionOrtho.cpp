////////////////////////////////////////////////////////////////////////////////////
/// @file ProjectionOrtho.cpp
/// @author DGI
/// @date 2006-12-15
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <GL/gl.h>
#include "ProjectionOrtho.h"
#include "Vue.h"
#include "iostream"


namespace vue {


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn ProjectionOrtho::ProjectionOrtho(int xMinCloture, int xMaxCloture, int yMinCloture, int yMaxCloture, double zAvant,  double zArriere, double zoomInMax, double zoomOutMax, double incrementZoom, double xMinFenetre, double xMaxFenetre, double yMinFenetre, double yMaxFenetre)
	///
	/// Constructeur d'une projection orthogonale.  Ne fait qu'assigner les
	/// variables membres et ajuste ensuite le rapport d'aspect.
	///
	/// @param[in] xMinCloture   : coordonn�e minimale en @a x de la cl�ture.
	/// @param[in] xMaxCloture   : coordonn�e maximale en @a x de la cl�ture.
	/// @param[in] yMinCloture   : coordonn�e minimale en @a y de la cl�ture.
	/// @param[in] yMaxCloture   : coordonn�e maximale en @a y de la cl�ture.
	/// @param[in] zAvant        : distance du plan avant (en @a z).
	/// @param[in] zArriere      : distance du plan arri�re (en @a z).
	/// @param[in] zoomInMax     : facteur de zoom in maximal.
	/// @param[in] zoomOutMax    : facteur de zoom out maximal.
	/// @param[in] incrementZoom : distance du plan arri�re (en @a z).
	/// @param[in] xMinFenetre   : coordonn�e minimale en @a x de la fen�tre
	///                            virtuelle.
	/// @param[in] xMaxFenetre   : coordonn�e maximale en @a x de la fen�tre
	///                            virtuelle.
	/// @param[in] yMinFenetre   : coordonn�e minimale en @a y de la fen�tre
	///                            virtuelle.
	/// @param[in] yMaxFenetre   : coordonn�e maximale en @a y de la fen�tre
	///                            virtuelle.
	/// 
	/// @return Aucune (constructeur).
	///
	////////////////////////////////////////////////////////////////////////
	ProjectionOrtho::ProjectionOrtho(int xMinCloture, int xMaxCloture,
		int yMinCloture, int yMaxCloture,
		double zAvant, double zArriere,
		double zoomInMax, double zoomOutMax,
		double incrementZoom,
		double xMinFenetre, double xMaxFenetre,
		double yMinFenetre, double yMaxFenetre) :
		Projection{ xMinCloture, xMaxCloture, yMinCloture, yMaxCloture,
		zAvant, zArriere,
		zoomInMax, zoomOutMax, incrementZoom, false },
		xMinFenetre_{ xMinFenetre },
		xMaxFenetre_{ xMaxFenetre },
		yMinFenetre_{ yMinFenetre },
		yMaxFenetre_{ yMaxFenetre }
	{
		ajusterRapportAspect();
		mettreAJourCloture();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerIn()
	///
	/// Permet de faire un zoom in selon l'incr�ment de zoom.
	/// 
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::zoomerIn()
	{
		if (nbZoom > -8)
		{
			xMaxFenetre_ = xMaxFenetre_ / (incrementZoom_);
			yMaxFenetre_ = yMaxFenetre_ / (incrementZoom_);
			xMinFenetre_ = xMinFenetre_ / (incrementZoom_);
			yMinFenetre_ = yMinFenetre_ / (incrementZoom_);
			nbZoom--;
			ajusterRapportAspect();
		}
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerOut()
	///
	/// Permet de faire un zoom out selon l'incr�ment de zoom.
	///
	/// @return Aucune.
	///
	//////////////////////////////////////////////////////////////////////// 
	void ProjectionOrtho::zoomerOut()
	{
		if (nbZoom < 5)
		{
			xMaxFenetre_ = (incrementZoom_)*xMaxFenetre_;
			yMaxFenetre_ = (incrementZoom_)*yMaxFenetre_;
			xMinFenetre_ = (incrementZoom_)*xMinFenetre_;
			yMinFenetre_ = (incrementZoom_)*yMinFenetre_;
			nbZoom++;
			ajusterRapportAspect();
		}
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::redimensionnerFenetre( const glm::ivec2& coinMin, const glm::ivec2& coinMax )
	///
	/// Permet d'ajuster les coordonn�es de la fen�tre virtuelle en fonction
	/// d'un redimensionnement de la fen�tre.
	///
	/// L'agrandissement de la fen�tre virtuelle est proportionnel �
	/// l'agrandissement de la clot�re afin que les objets gardent la m�me
	/// grandeur apparente lorsque la fen�tre est redimensionn�e.
	///
	/// @param[in]  coinMin : Coin contenant les coordonn�es minimales de la
	///                       nouvelle cl�ture
	/// @param[in]  coinMax : Coin contenant les coordonn�es maximales de la
	///                       nouvelle cl�ture
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::redimensionnerFenetre(const glm::ivec2& coinMin,
		const glm::ivec2& coinMax)
	{
		double ratiox = coinMax.x - xMaxCloture_;
		double ratioy = coinMax.y - yMaxCloture_;

		ratiox = ratiox*((xMaxFenetre_ - xMinFenetre_) / xMaxCloture_);
		ratioy = ratioy*((yMaxFenetre_ - yMinFenetre_) / yMaxCloture_);

		xMinFenetre_ = xMinFenetre_ - ratiox / 2;
		yMinFenetre_ = yMinFenetre_ - ratioy / 2;

		xMaxFenetre_ = xMaxFenetre_ - ratiox / 2;
		yMaxFenetre_ = yMaxFenetre_ - ratioy / 2;

		xMinCloture_ = coinMin.x;
		yMaxCloture_ = coinMin.y;
		xMaxCloture_ = coinMax.x;
		yMaxCloture_ = coinMax.y;

		ajusterRapportAspect();
		mettreAJourCloture();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::appliquer() const
	///
	/// Cette fonction permet d'appliquer la fen�tre virtuelle en appelant les
	/// fonctions d'OpenGL selon le type de projection et les propri�t�s de la
	/// fen�tre.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::appliquer() const
	{
		glOrtho(xMinFenetre_, xMaxFenetre_,
			yMinFenetre_, yMaxFenetre_,
			zAvant_, zArriere_);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerIn( const glm::ivec2& coin1, const glm::ivec2& coin2)
	///
	/// Permet de faire un zoom in sur un rectangle d�termin� par deux coins.
	/// Ainsi la r�gion d�limit�e par le rectangle deviendra la fen�tre
	/// virtuelle.  La fen�tre r�sultante est ajust�e pour respecter le rapport
	/// d'aspect.
	///
	/// @param[in]  coin1 : Le premier coin du rectangle.
	/// @param[in]  coin2 : Le deuxi�me coin du rectangle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::zoomerIn(const glm::dvec3& coin1, const glm::dvec3& coin2)
	{
		double longueurXElast = abs(coin1.x - coin2.x);
		double longueurYElast = abs(coin1.y - coin2.y);
		double diagonaleElast = sqrt((longueurXElast*longueurXElast) + (longueurYElast*longueurYElast));		 
		
		double diffX = xMaxCloture_ - xMinCloture_;
		double diffy = yMaxCloture_ - yMinCloture_;
		double diagonaleCloture = sqrt((diffX*diffX) + (diffy*diffy));

		double rapportDiago = diagonaleCloture / diagonaleElast;

		xMaxFenetre_ = xMaxFenetre_*rapportDiago;
		yMaxFenetre_ = yMaxFenetre_*rapportDiago;

		xMinFenetre_ = xMinFenetre_ * rapportDiago;
		yMinFenetre_ = yMinFenetre_ * rapportDiago;

		centrerSurPoint(centre_);
		ajusterRapportAspect();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::zoomerOut( const glm::ivec2& coin1, const glm::ivec2& coin2)
	///
	/// Permet de faire un zoom out sur un rectangle d�limit� par deux coins.
	/// Ainsi la fen�tre virtuelle avant le zoom sera plac�e � l'interieur de
	/// la r�gion d�limit� par le rectangle.  La fen�tre r�sultante est ajust�e
	/// pour respecter le rapport d'aspect.
	///
	/// @param[in]  coin1 : Le premier coin du rectangle.
	/// @param[in]  coin2 : Le deuxi�me coin du rectangle.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::zoomerOut(const glm::dvec3& coin1, const glm::dvec3& coin2)
	{
		double longueurXElast = abs(coin1.x - coin2.x);
		double longueurYElast = abs(coin1.y - coin2.y);
		double diagonaleElast = sqrt((longueurXElast*longueurXElast) + (longueurYElast*longueurYElast));

		double diffX = xMaxCloture_ - xMinCloture_;
		double diffy = yMaxCloture_ - yMinCloture_;
		double diagonaleCloture = sqrt((diffX*diffX) + (diffy*diffy));

		double rapportDiago = diagonaleCloture / diagonaleElast;

		xMaxFenetre_ = xMaxFenetre_*rapportDiago;
		yMaxFenetre_ = yMaxFenetre_*rapportDiago;

		xMinFenetre_ = xMinFenetre_ * rapportDiago;
		yMinFenetre_ = yMinFenetre_ * rapportDiago;

		centrerSurPoint(centre_);
		ajusterRapportAspect();
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::translater( double deplacementX, double deplacementY )
	///
	/// Permet de d�placer la fen�tre virtuelle en @a x et en @a y.  Les
	/// d�placement doivent �tre exprim�s en proportion de la fen�tre virtuelle.
	///
	/// @param[in]  deplacementX : le d�placement en @a x.
	/// @param[in]  deplacementY : le d�placement en @a y.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::translater(double deplacementX, double deplacementY)
	{
		double diffx = xMaxFenetre_ - xMinFenetre_;
		double diffy = yMaxFenetre_ - yMinFenetre_;

		double deplX = diffx * 0.1;
		double deplY = diffy * 0.1;

		//deplacement � droite
		if (deplacementX == 1 && deplacementY == 0)
		{
			xMaxFenetre_ = xMaxFenetre_ - deplX;
			xMinFenetre_ = xMinFenetre_ - deplX;
		}  

		//deplacement � gauche
		else if (deplacementX == -1 && deplacementY == 0)
		{
			xMaxFenetre_ = xMaxFenetre_ + deplX;
			xMinFenetre_ = xMinFenetre_ + deplX;
		}

		//deplacement en haut
		else if (deplacementX == 0 && deplacementY == 1)
		{
			yMaxFenetre_ = yMaxFenetre_ - deplY;
			yMinFenetre_ = yMinFenetre_ - deplY;
		}

		//deplacement en bas
		else if (deplacementX == 0 && deplacementY == -1)
		{
			yMaxFenetre_ = yMaxFenetre_ + deplY;
			yMinFenetre_ = yMinFenetre_ + deplY;
		}

		else
		{
			xMaxFenetre_ = xMaxFenetre_ + deplacementX;
			xMinFenetre_ = xMinFenetre_ + deplacementX;
			yMaxFenetre_ = yMaxFenetre_ + deplacementY;
			yMinFenetre_ = yMinFenetre_ + deplacementY;
		}

		centre_ = glm::ivec2((xMaxFenetre_ + xMinFenetre_) / 2, (yMaxFenetre_ + yMinFenetre_) / 2);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::translater(const glm::ivec2& deplacement)
	///
	/// Permet de translater la fen�tre virtuelle en fonction d'un d�placement
	/// en coordonn�es de cl�ture.
	///
	/// @param[in]  deplacement : Le d�placement en coordonn�es de cl�ture.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::translater(const glm::dvec2& deplacement)
	{
		xMaxFenetre_ = xMaxFenetre_ + deplacement.x;
		xMinFenetre_ = xMinFenetre_ + deplacement.x;
		yMaxFenetre_ = yMaxFenetre_ + deplacement.y;
		yMinFenetre_ = yMinFenetre_ + deplacement.y;

		centre_ = glm::dvec2((xMaxFenetre_ + xMinFenetre_) / 2, (yMaxFenetre_ + yMinFenetre_) / 2);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::centrerSurPoint( const glm::ivec2& pointCentre )
	///
	/// Permet de centrer la fen�tre virtuelle sur un point de l'�cran. Le
	/// point de l'�cran est convertit en coordonn�es virtuelles et il devient
	/// le centre de la fen�tre virtuelle.
	///
	/// @param[in]  pointCentre : Le point sur lequel on doit centrer.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::centrerSurPoint(const glm::dvec2& pointCentre)
	{
		double xTranslate = pointCentre.x - (xMaxFenetre_ + xMinFenetre_) / 2;
		double yTranslate = pointCentre.y - (yMaxFenetre_ + yMinFenetre_) / 2;

		centre_ = glm::dvec2(xTranslate, yTranslate);

		translater(centre_);
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void ProjectionOrtho::ajusterRapportAspect()
	///
	/// Permet d'ajuster les coordonn�es de la fen�tre virtuelle en fonction
	/// de la cl�ture de fa�on � ce que le rapport d'aspect soit respect�.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	void ProjectionOrtho::ajusterRapportAspect()
	{
		if ((xMaxFenetre_ - xMinFenetre_)*(double)yMaxCloture_ / (double)xMaxCloture_ >= (yMaxFenetre_ - yMinFenetre_)*(double)xMaxCloture_ / (double)yMaxCloture_)
		{
			yMinFenetre_ = (xMinFenetre_)*(double)yMaxCloture_ / (double)(xMaxCloture_);
			yMaxFenetre_ = (xMaxFenetre_)*(double)yMaxCloture_ / (double)(xMaxCloture_);
		}
		else
		{
			xMinFenetre_ = yMinFenetre_*(double)xMaxCloture_ / (double)(yMaxCloture_);
			xMaxFenetre_ = yMaxFenetre_*(double)xMaxCloture_ / (double)(yMaxCloture_);
		}
		centrerSurPoint(centre_);
	}

}; // Fin du namespace vue.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
