using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InterfaceGraphique.patron_state
{
    /// <summary>
    /// Etat utilise pour svoir si on est dans le mode test
    /// </summary>
    class TestState : AbstractState
    {
        /// <summary>
        /// Inutile ici, les animations du mode test sont faites par la fonction animer 
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        public override void Action(int x, int y)
        {
        }
    }
}
