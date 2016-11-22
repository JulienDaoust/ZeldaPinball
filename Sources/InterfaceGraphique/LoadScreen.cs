using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    /// <summary>
    /// Fenetre d'attente dans le mode campagne
    /// </summary>
    public partial class LoadScreen : Form
    {
        /// <summary>
        /// Seconde ecoulee depuis le debut de l'affichage
        /// </summary>
        int secondeEcoulees;
        /// <summary>
        /// zone de jeu qui va s'afficher
        /// </summary>
        ZoneDeJeux zone_;
        /// <summary>
        /// Constructeur qui prend la zone en entree
        /// </summary>
        /// <param name="zone">zone courante</param>
        public LoadScreen(ZoneDeJeux zone)
        {
            InitializeComponent();
            zone_ = zone;
            initialiserAffichage();
            this.KeyDown += new KeyEventHandler(ToucheDown);

            timer1.Enabled = true;
            secondeEcoulees = 0;
        }

        /// <summary>
        /// configuration d'affichage
        /// </summary>
        private void initialiserAffichage() 
        {
            label5.Text = "5";
            labelNomPartie.Text = zone_.nom_;
            labelDifficulte.Text = zone_.difficulte_.ToString();
            labelPoints.Text = zone_.pointsSeuil_.ToString();
        
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            this.Close();

        }


        private void ToucheDown(Object o, KeyEventArgs e)
        {
            if (e.KeyValue == (char)Keys.Space)
            {
                this.Close();
            }
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            secondeEcoulees++;
            label5.Text = (timer1.Interval/1000 - secondeEcoulees).ToString();
        }
    }
}
