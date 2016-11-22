using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.IO;

namespace InterfaceGraphique
{
    /// <summary>
    /// Cette classe représente les configurations associés a une partie
    /// Rapide ou a un campagne
    /// </summary>
    public class ConfigurationPartie
    {
        /// <summary>
        /// type de partieRapide multijouer défini par l'utilisateur dans le 
        /// menu de configuration de partieRapide
        /// </summary>
        public bool joueurVirtuel_;
        public bool estMultiplayer_;

        /// <summary>
        /// billes initiales par partieRapide déterminé dans le fichier 
        /// de configurations Config.txt
        /// </summary>
        public int billesInitialles_;

        /// <summary>
        /// constructeur pour une partieRapide
        /// </summary>
        public ConfigurationPartie()
        {
            joueurVirtuel_ = false;
            estMultiplayer_ = false;

            //récupere le nombre de billes du fichier de configuration
            string pathConfig = Application.StartupPath + "/données/Config.txt";
            string[] lines = System.IO.File.ReadAllLines(pathConfig);
            billesInitialles_ = Convert.ToInt32(lines[5]);
        }

    }
}
