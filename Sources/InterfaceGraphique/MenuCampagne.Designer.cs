namespace InterfaceGraphique
{
    partial class MenuCampagne
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.groupBoxChoixZone = new System.Windows.Forms.GroupBox();
            this.button1 = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.listBoxZones = new System.Windows.Forms.ListBox();
            this.comboBoxZones = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.buttonSuprimer1 = new System.Windows.Forms.Button();
            this.buttonSuprimer = new System.Windows.Forms.Button();
            this.buttonDemarer = new System.Windows.Forms.Button();
            this.buttonAnuler = new System.Windows.Forms.Button();
            this.groupBoxDeuxiemmeJoueur = new System.Windows.Forms.GroupBox();
            this.radioButtonHumain = new System.Windows.Forms.RadioButton();
            this.radioVirtuel = new System.Windows.Forms.RadioButton();
            this.groupChoixTypePartie = new System.Windows.Forms.GroupBox();
            this.radioSinglePlayer = new System.Windows.Forms.RadioButton();
            this.radioButtonCoop = new System.Windows.Forms.RadioButton();
            this.groupBoxChoixZone.SuspendLayout();
            this.groupBoxDeuxiemmeJoueur.SuspendLayout();
            this.groupChoixTypePartie.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBoxChoixZone
            // 
            this.groupBoxChoixZone.Controls.Add(this.button1);
            this.groupBoxChoixZone.Controls.Add(this.label2);
            this.groupBoxChoixZone.Controls.Add(this.listBoxZones);
            this.groupBoxChoixZone.Controls.Add(this.comboBoxZones);
            this.groupBoxChoixZone.Controls.Add(this.label1);
            this.groupBoxChoixZone.Controls.Add(this.buttonSuprimer1);
            this.groupBoxChoixZone.Controls.Add(this.buttonSuprimer);
            this.groupBoxChoixZone.Location = new System.Drawing.Point(56, 190);
            this.groupBoxChoixZone.Margin = new System.Windows.Forms.Padding(4);
            this.groupBoxChoixZone.Name = "groupBoxChoixZone";
            this.groupBoxChoixZone.Padding = new System.Windows.Forms.Padding(4);
            this.groupBoxChoixZone.Size = new System.Drawing.Size(548, 377);
            this.groupBoxChoixZone.TabIndex = 11;
            this.groupBoxChoixZone.TabStop = false;
            this.groupBoxChoixZone.Text = "Choisir une zone de jeux";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(20, 152);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(146, 88);
            this.button1.TabIndex = 13;
            this.button1.Text = "Campagne Sauvegardé";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(236, 38);
            this.label2.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(245, 25);
            this.label2.TabIndex = 12;
            this.label2.Text = "Zone(s) de la campagne";
            // 
            // listBoxZones
            // 
            this.listBoxZones.ItemHeight = 25;
            this.listBoxZones.Location = new System.Drawing.Point(242, 67);
            this.listBoxZones.Margin = new System.Windows.Forms.Padding(4);
            this.listBoxZones.Name = "listBoxZones";
            this.listBoxZones.Size = new System.Drawing.Size(226, 229);
            this.listBoxZones.TabIndex = 11;
            // 
            // comboBoxZones
            // 
            this.comboBoxZones.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxZones.Location = new System.Drawing.Point(20, 67);
            this.comboBoxZones.Margin = new System.Windows.Forms.Padding(4);
            this.comboBoxZones.Name = "comboBoxZones";
            this.comboBoxZones.Size = new System.Drawing.Size(200, 33);
            this.comboBoxZones.TabIndex = 8;
            this.comboBoxZones.SelectionChangeCommitted += new System.EventHandler(this.comboBoxZones_SelectionChangeCommitted_1);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(14, 38);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(152, 25);
            this.label1.TabIndex = 6;
            this.label1.Text = "Choix de Zone";
            // 
            // buttonSuprimer1
            // 
            this.buttonSuprimer1.Location = new System.Drawing.Point(242, 302);
            this.buttonSuprimer1.Margin = new System.Windows.Forms.Padding(4);
            this.buttonSuprimer1.Name = "buttonSuprimer1";
            this.buttonSuprimer1.Size = new System.Drawing.Size(52, 37);
            this.buttonSuprimer1.TabIndex = 10;
            this.buttonSuprimer1.Text = "-";
            this.buttonSuprimer1.UseVisualStyleBackColor = true;
            this.buttonSuprimer1.Click += new System.EventHandler(this.buttonSuprimer1_Click);
            // 
            // buttonSuprimer
            // 
            this.buttonSuprimer.Location = new System.Drawing.Point(390, 302);
            this.buttonSuprimer.Margin = new System.Windows.Forms.Padding(4);
            this.buttonSuprimer.Name = "buttonSuprimer";
            this.buttonSuprimer.Size = new System.Drawing.Size(82, 37);
            this.buttonSuprimer.TabIndex = 10;
            this.buttonSuprimer.Text = "Clear";
            this.buttonSuprimer.UseVisualStyleBackColor = true;
            this.buttonSuprimer.Click += new System.EventHandler(this.buttonSuprimer_Click);
            // 
            // buttonDemarer
            // 
            this.buttonDemarer.Enabled = false;
            this.buttonDemarer.Location = new System.Drawing.Point(462, 596);
            this.buttonDemarer.Margin = new System.Windows.Forms.Padding(4);
            this.buttonDemarer.Name = "buttonDemarer";
            this.buttonDemarer.Size = new System.Drawing.Size(140, 48);
            this.buttonDemarer.TabIndex = 9;
            this.buttonDemarer.Text = "Démarer";
            this.buttonDemarer.UseVisualStyleBackColor = true;
            this.buttonDemarer.Click += new System.EventHandler(this.buttonDemarer_Click);
            // 
            // buttonAnuler
            // 
            this.buttonAnuler.Location = new System.Drawing.Point(56, 596);
            this.buttonAnuler.Margin = new System.Windows.Forms.Padding(4);
            this.buttonAnuler.Name = "buttonAnuler";
            this.buttonAnuler.Size = new System.Drawing.Size(140, 48);
            this.buttonAnuler.TabIndex = 10;
            this.buttonAnuler.Text = "Annuler";
            this.buttonAnuler.UseVisualStyleBackColor = true;
            this.buttonAnuler.Click += new System.EventHandler(this.buttonAnuler_Click);
            // 
            // groupBoxDeuxiemmeJoueur
            // 
            this.groupBoxDeuxiemmeJoueur.Controls.Add(this.radioButtonHumain);
            this.groupBoxDeuxiemmeJoueur.Controls.Add(this.radioVirtuel);
            this.groupBoxDeuxiemmeJoueur.Location = new System.Drawing.Point(352, 38);
            this.groupBoxDeuxiemmeJoueur.Margin = new System.Windows.Forms.Padding(4);
            this.groupBoxDeuxiemmeJoueur.Name = "groupBoxDeuxiemmeJoueur";
            this.groupBoxDeuxiemmeJoueur.Padding = new System.Windows.Forms.Padding(4);
            this.groupBoxDeuxiemmeJoueur.Size = new System.Drawing.Size(250, 123);
            this.groupBoxDeuxiemmeJoueur.TabIndex = 7;
            this.groupBoxDeuxiemmeJoueur.TabStop = false;
            this.groupBoxDeuxiemmeJoueur.Text = "Deuxièmme joueur";
            this.groupBoxDeuxiemmeJoueur.Visible = false;
            // 
            // radioButtonHumain
            // 
            this.radioButtonHumain.AutoSize = true;
            this.radioButtonHumain.Checked = true;
            this.radioButtonHumain.Location = new System.Drawing.Point(20, 35);
            this.radioButtonHumain.Margin = new System.Windows.Forms.Padding(4);
            this.radioButtonHumain.Name = "radioButtonHumain";
            this.radioButtonHumain.Size = new System.Drawing.Size(116, 29);
            this.radioButtonHumain.TabIndex = 0;
            this.radioButtonHumain.TabStop = true;
            this.radioButtonHumain.Text = "Humain";
            this.radioButtonHumain.UseVisualStyleBackColor = true;
            this.radioButtonHumain.CheckedChanged += new System.EventHandler(this.radioButtonHumain_CheckedChanged);
            // 
            // radioVirtuel
            // 
            this.radioVirtuel.AutoSize = true;
            this.radioVirtuel.Location = new System.Drawing.Point(24, 73);
            this.radioVirtuel.Margin = new System.Windows.Forms.Padding(4);
            this.radioVirtuel.Name = "radioVirtuel";
            this.radioVirtuel.Size = new System.Drawing.Size(104, 29);
            this.radioVirtuel.TabIndex = 1;
            this.radioVirtuel.Text = "Virtuel";
            this.radioVirtuel.UseVisualStyleBackColor = true;
            this.radioVirtuel.CheckedChanged += new System.EventHandler(this.radioVirtuel_CheckedChanged);
            // 
            // groupChoixTypePartie
            // 
            this.groupChoixTypePartie.Controls.Add(this.radioSinglePlayer);
            this.groupChoixTypePartie.Controls.Add(this.radioButtonCoop);
            this.groupChoixTypePartie.Location = new System.Drawing.Point(56, 38);
            this.groupChoixTypePartie.Margin = new System.Windows.Forms.Padding(4);
            this.groupChoixTypePartie.Name = "groupChoixTypePartie";
            this.groupChoixTypePartie.Padding = new System.Windows.Forms.Padding(4);
            this.groupChoixTypePartie.Size = new System.Drawing.Size(269, 123);
            this.groupChoixTypePartie.TabIndex = 8;
            this.groupChoixTypePartie.TabStop = false;
            this.groupChoixTypePartie.Text = "Type de partieRapide";
            // 
            // radioSinglePlayer
            // 
            this.radioSinglePlayer.AutoSize = true;
            this.radioSinglePlayer.Checked = true;
            this.radioSinglePlayer.Location = new System.Drawing.Point(20, 31);
            this.radioSinglePlayer.Margin = new System.Windows.Forms.Padding(4);
            this.radioSinglePlayer.Name = "radioSinglePlayer";
            this.radioSinglePlayer.Size = new System.Drawing.Size(86, 29);
            this.radioSinglePlayer.TabIndex = 0;
            this.radioSinglePlayer.TabStop = true;
            this.radioSinglePlayer.Text = "Solo";
            this.radioSinglePlayer.UseVisualStyleBackColor = true;
            this.radioSinglePlayer.CheckedChanged += new System.EventHandler(this.radioSinglePlayer_CheckedChanged);
            // 
            // radioButtonCoop
            // 
            this.radioButtonCoop.AutoSize = true;
            this.radioButtonCoop.Location = new System.Drawing.Point(20, 65);
            this.radioButtonCoop.Margin = new System.Windows.Forms.Padding(4);
            this.radioButtonCoop.Name = "radioButtonCoop";
            this.radioButtonCoop.Size = new System.Drawing.Size(159, 29);
            this.radioButtonCoop.TabIndex = 1;
            this.radioButtonCoop.Text = "Coopérative";
            this.radioButtonCoop.UseVisualStyleBackColor = true;
            this.radioButtonCoop.CheckedChanged += new System.EventHandler(this.radioButtonCoop_CheckedChanged);
            // 
            // MenuCampagne
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(659, 683);
            this.Controls.Add(this.groupBoxChoixZone);
            this.Controls.Add(this.buttonDemarer);
            this.Controls.Add(this.buttonAnuler);
            this.Controls.Add(this.groupBoxDeuxiemmeJoueur);
            this.Controls.Add(this.groupChoixTypePartie);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "MenuCampagne";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "ConfigurationCampagne";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.ConfigurationCampagne_FormClosed);
            this.groupBoxChoixZone.ResumeLayout(false);
            this.groupBoxChoixZone.PerformLayout();
            this.groupBoxDeuxiemmeJoueur.ResumeLayout(false);
            this.groupBoxDeuxiemmeJoueur.PerformLayout();
            this.groupChoixTypePartie.ResumeLayout(false);
            this.groupChoixTypePartie.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBoxChoixZone;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button buttonDemarer;
        private System.Windows.Forms.Button buttonAnuler;
        private System.Windows.Forms.GroupBox groupBoxDeuxiemmeJoueur;
        private System.Windows.Forms.RadioButton radioButtonHumain;
        private System.Windows.Forms.RadioButton radioVirtuel;
        private System.Windows.Forms.GroupBox groupChoixTypePartie;
        private System.Windows.Forms.RadioButton radioSinglePlayer;
        private System.Windows.Forms.RadioButton radioButtonCoop;
        private System.Windows.Forms.ListBox listBoxZones;
        private System.Windows.Forms.Button buttonSuprimer;
        private System.Windows.Forms.ComboBox comboBoxZones;
        private System.Windows.Forms.Button buttonSuprimer1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button button1;
    }
}