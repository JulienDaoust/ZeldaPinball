using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Windows.Forms;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InterfaceGraphique
{
    /// <summary>
    /// Cette classe représente un zone de jeux. 
    /// Elle contiens ls informations pertinantes de celle-ci
    /// </summary>
    public partial class ZoneDeJeux : IComparable
    {

        public string path_;
        public string nom_;
        //Dificulte de la zone
        public int difficulte_;

        //score a ateindre pour sortir de la zone
        public int pointsSeuil_;
      
        //Points requis pour obtenir une bille gratuite
        public int pointsBilleGratuite_;

        
 
        /// <summary>
        /// Constructeur par parametres
        /// </summary>
        /// <param name="fichierChoisi"></param>
        /// <param name="nom"></param>
        /// <param name="dificulte"></param>
        public ZoneDeJeux( string fichierChoisi, string nom, int dificulte)
        {
            this.nom_ = nom;
            this.path_ = fichierChoisi;
            this.difficulte_ = dificulte;
        }
        
        /// <summary>
        /// constructeur par défault
        /// </summary>
        public ZoneDeJeux() 
        {
            this.nom_ = "Default";
            this.path_ = Application.StartupPath + @"\zones\default.xml\0";
            this.difficulte_ = 0;
        }

        /// <summary>
        /// Modifie les caracteristiques de la zone
        /// </summary>
        /// <param name="fichierChoisi"></param>
        /// <param name="nom"></param>
        /// <param name="difficulte"></param>
        public void actualiserZone(string fichierChoisi, string nom, int difficulte)
        {
            this.nom_ = nom;
            this.path_ = fichierChoisi;
            this.difficulte_ = difficulte;
         
        }

        /// <summary>
        /// Surcharge de ICompareTo pour permetre le trie en ordre de difficulte_
        /// </summary>
        /// <param name="obj2"></param>
        /// <returns></returns>
        public int CompareTo(object obj2) 
        {
            ZoneDeJeux zone2 = obj2 as ZoneDeJeux;
            if (zone2 != null)
                return this.difficulte_.CompareTo(zone2.difficulte_);
            else
                throw new ArgumentException("La zone de jeux compare nest pas une zone valide");
        }


    }
    
}
