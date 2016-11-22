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

namespace InterfaceGraphique
{
    /// <summary>
    /// Fenetre pour definir les proprietes d'une zone
    /// </summary>
    public partial class Propriete : Form
    {
        int pointsButoirCirculaire = FonctionsNatives.obtenirPointsButoirCirculaire();
        int pointsButoirTriangulaire = FonctionsNatives.obtenirPointsButoirTriangulaire();
        int pointsButoirCible = FonctionsNatives.obtenirPointsCible();
        int pointsZoneSuivante = FonctionsNatives.obtenirPointsNiveauSuivant();
        int pointsBillesBonus = FonctionsNatives.obtenirPointsBilleBonus();
        int difficulte = FonctionsNatives.obtenirDifficulteProp();
        bool valider1 = false, valider2 = false, valider3 = false, valider4 = false, valider5 = false;

        /// <summary>
        /// Constructeur par default
        /// </summary>
        public Propriete()
        {
            InitializeComponent();
            textBox1.Text = pointsButoirCirculaire.ToString();
            textBox2.Text = pointsButoirTriangulaire.ToString();
            textBox3.Text = pointsButoirCible.ToString();
            textBox4.Text = pointsZoneSuivante.ToString();
            textBox5.Text = pointsBillesBonus.ToString();
            comboBox1.Text = difficulte.ToString();
        }

        /// <summary>
        /// Si on clique sur appliquer on assigne les variables si tout a ete valider
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button1_Click(object sender, EventArgs e)
        {
            if (valider1 && valider2 && valider3 && valider4 && valider5)
            {
                FonctionsNatives.assignerPointsButoirTriangulaire(pointsButoirTriangulaire);
                FonctionsNatives.assignerPointsButoirCirculaire(pointsButoirCirculaire);
                FonctionsNatives.assignerPointsCible(pointsButoirCible);
                FonctionsNatives.assignerPointsNiveauSuivant(pointsZoneSuivante);
                FonctionsNatives.assignerPointsBilleBonus(pointsBillesBonus);
                FonctionsNatives.assignerDifficulte(difficulte);
                this.Close();
            }
            else
                MessageBox.Show("Erreur, une des entrees n'est pas valider");
        }

        /// <summary>
        /// Bouton annullee
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        /// <summary>
        /// Valider la textBox1
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button3_Click(object sender, EventArgs e)
        {
            string valeurString;
            double valeurNumDouble;
            int valeurNum;
            valeurString = textBox1.Text;
            bool parse = Double.TryParse(valeurString, out valeurNumDouble);
            if (parse)
            {
                if (valeurNumDouble >= 1 && valeurNumDouble <= 500)
                {
                    valeurNum = Convert.ToInt32(valeurNumDouble);
                    pointsButoirCirculaire = valeurNum;
                    valider1 = true;
                }
                else
                {
                    MessageBox.Show("Erreur, entree invalide");
                    pointsButoirCirculaire = 10;
                    valider1 = false;
                }
            }
            else
            {
                MessageBox.Show("Erreur, entree invalide");
                pointsButoirCirculaire = 10;
                valider1 = false;
            }
        }

        /// <summary>
        /// Valider la textBox2
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button4_Click(object sender, EventArgs e)
        {
            string valeurString;
            double valeurNumDouble;
            int valeurNum;
            valeurString = textBox2.Text;
            bool parse = Double.TryParse(valeurString, out valeurNumDouble);
            if (parse)
            {
                if (valeurNumDouble >= 1 && valeurNumDouble <= 500)
                {
                    valeurNum = Convert.ToInt32(valeurNumDouble);
                    pointsButoirTriangulaire = valeurNum;
                    valider2 = true;
                }
                else
                {
                    MessageBox.Show("Erreur, entree invalide");
                    pointsButoirTriangulaire = 10;
                    valider2 = false;
                }
            }
            else
            {
                MessageBox.Show("Erreur, entree invalide");
                pointsButoirTriangulaire = 10;
                valider2 = false;
            }
        }

        /// <summary>
        /// Valider la textBox3
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button5_Click(object sender, EventArgs e)
        {
            string valeurString;
            double valeurNumDouble;
            int valeurNum;
            valeurString = textBox3.Text;
            bool parse = Double.TryParse(valeurString, out valeurNumDouble);
            if (parse)
            {
                if (valeurNumDouble >= 1 && valeurNumDouble <= 500)
                {
                    valeurNum = Convert.ToInt32(valeurNumDouble);
                    pointsButoirCible = valeurNum;
                    valider3 = true;
                }
                else
                {
                    MessageBox.Show("Erreur, entree invalide");
                    pointsZoneSuivante = 1000;
                    valider3 = false;
                }
            }
            else
            {
                MessageBox.Show("Erreur, entree invalide");
                pointsZoneSuivante = 1000;
                valider3 = false;
            }
        }

        /// <summary>
        /// Valider la textBox4
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button6_Click(object sender, EventArgs e)
        {
            string valeurString;
            double valeurNumDouble;
            int valeurNum;
            valeurString = textBox4.Text;
            bool parse = Double.TryParse(valeurString, out valeurNumDouble);
            if (parse)
            {
                if (valeurNumDouble >= 100 && valeurNumDouble <= 10000)
                {
                    valeurNum = Convert.ToInt32(valeurNumDouble);
                    pointsZoneSuivante = valeurNum;
                    valider4 = true;
                }
                else
                {
                    MessageBox.Show("Erreur, entree invalide");
                    pointsZoneSuivante = 1000;
                    valider4 = false;
                }
            }
            else
            {
                MessageBox.Show("Erreur, entree invalide");
                pointsZoneSuivante = 1000;
                valider4 = false;
            }
        }

        /// <summary>
        /// Valider la textBox5
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button7_Click(object sender, EventArgs e)
        {
            string valeurString;
            double valeurNumDouble;
            int valeurNum;
            valeurString = textBox5.Text;
            bool parse = Double.TryParse(valeurString, out valeurNumDouble);
            if (parse)
            {
                if (valeurNumDouble >= 50 && valeurNumDouble <= 2000)
                {
                    valeurNum = Convert.ToInt32(valeurNumDouble);
                    pointsBillesBonus = valeurNum;
                    valider5 = true;
                }
                else
                {
                    MessageBox.Show("Erreur, entree invalide");
                    pointsBillesBonus = 200;
                    valider5 = false;
                }
            }
            else
            {
                MessageBox.Show("Erreur, entree invalide");
                pointsBillesBonus = 200;
                valider5 = false;
            }
        }

        /// <summary>
        /// Changement de difficulte
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            difficulte = Convert.ToInt32(comboBox1.Text);
        }

    }

    static partial class FonctionsNatives
    {
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerPointsButoirTriangulaire(int point);
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerPointsButoirCirculaire(int point);
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerPointsCible(int point);
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerPointsNiveauSuivant(int point);
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerPointsBilleBonus(int point);
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void assignerDifficulte(int point);
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirPointsButoirTriangulaire();
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirPointsButoirCirculaire();
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirPointsCible();
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirPointsNiveauSuivant();
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirPointsBilleBonus();
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirDifficulteProp();
    }
}
