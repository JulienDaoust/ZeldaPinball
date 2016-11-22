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
    public partial class MenuPrincipal : Form
    {

        Configuration config;
        ConfigurerPartieRapide configSimple;
        MenuCampagne configCampagne;
        PartieRapide partie;

        public MenuPrincipal()
        {
            InitializeComponent();
            config = new Configuration();
            partie = null;
        }

        private void labelPartieRapide_Click(object sender, EventArgs e)
        {
            Program.modeEditeur = null;
            this.Hide();
            configSimple = new ConfigurerPartieRapide();
            configSimple.Show();
        }
        private void labelCampagne_Click(object sender, EventArgs e)
        {
            Program.modeEditeur = null;
            this.Hide();
            configCampagne = new MenuCampagne();
            configCampagne.Show();
        }

        private void labelConfiguration_Click(object sender, EventArgs e)
        {
            this.Hide();
            config.Show();
        }

        private void labelEditeur_Click(object sender, EventArgs e)
        {
            partie = null;
            this.Hide();
            Program.modeEditeur = new ModeEditeur(this);
            Program.modeEditeur.Show();

        }

        private void labelQuiter_Click(object sender, EventArgs e)
        {
            if (System.Windows.Forms.Application.MessageLoop)
            {
                // WinForms app
                System.Windows.Forms.Application.Exit();
            }
            else
            {
                // Console app
                System.Environment.Exit(1);
            }
        }

        public void MettreAJour(double tempsInterAffichage)
        {
            try
            {
                this.Invoke((MethodInvoker)delegate
                {
                    if (Program.modeEditeur != null)
                        Program.modeEditeur.MettreAJour(tempsInterAffichage);
                    else if (partie != null)
                        partie.MettreAJour(tempsInterAffichage);
                    else
                    {
                        FonctionsNatives.animer(tempsInterAffichage);
                    }
                });
            }
            catch (Exception)
            {
            }

        }
    }
}
