using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace InterfaceGraphique
{
    /// <summary>
    /// Fenetre qui s'occupe d'enregistrer la touche entree par l'utilisateur dans les configurations
    /// </summary>
    public partial class KeyPress : Form
    {
        /// <summary>
        /// Si une touche a ete enfoncee ou non
        /// </summary>
        bool toucheEnfonce = false;
        /// <summary>
        /// La touche enfoncee par l'utilisateur
        /// </summary>
        Keys touche;
        /// <summary>
        /// Menu de configuration
        /// </summary>
        Configuration config;
        /// <summary>
        /// Constructeur par default
        /// </summary>
        public KeyPress()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Constructeur qui prend le menu de config en parametre
        /// </summary>
        /// <param name="cfg"></param>
        public KeyPress(Configuration cfg)
        {
            config = cfg;
            config.desactiverEntre();
            InitializeComponent();
        }
        /// <summary>
        /// Fonction qui est appellée lorsquon enfonce une key lorsque la fenetre est active
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>

        private void KeyPress_KeyDown(object sender, KeyEventArgs e)
        {
            if(toucheEnfonce == false)
            {
                toucheEnfonce = true;
                touche = e.KeyCode;
                config.activerEntre();
                config.toucheRecu(touche);
                this.Close();
            }
        }

        /// <summary>
        /// Retourne si une touche est enfonce
        /// </summary>
        /// <returns>vrai si elle est enfoncee, faux autrement</returns>
        public bool isEnfonce()
        {
            return toucheEnfonce;
        }

        private void KeyPress_FormClosed(object sender, FormClosedEventArgs e)
        {
            config.activerEntre();
        }
    }
}
