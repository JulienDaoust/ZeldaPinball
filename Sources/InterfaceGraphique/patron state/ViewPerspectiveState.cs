﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.Drawing;

namespace InterfaceGraphique.patron_state
{
    /// <summary>
    /// Etat de selection
    /// </summary>
    class ViewPerspectiveState : AbstractState
    {
        /// <summary>
        /// 
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        public override void Action(int x, int y)
        {
            if (lastPos_ != new Point())
            {
                double rotX = (x - lastPos_.X); 
                if(rotX != 0)
                    rotX /= Math.Abs(x - lastPos_.X);
                double rotY = (y - lastPos_.Y);
                if(rotY != 0)
                   rotY /= Math.Abs(y - lastPos_.Y);
                FonctionsNatives.rotaterXY(rotX * 0.02, rotY * 0.02);
                lastPos_ = new Point(x, y);
            }
        }
        public void init(int x, int y)
        {
            lastPos_ = new Point(x, y);
        }
        private Point lastPos_;
    }
    static partial class FonctionsNatives
    {
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void rotaterXY(double rotationX, double rotationY);
    }
}