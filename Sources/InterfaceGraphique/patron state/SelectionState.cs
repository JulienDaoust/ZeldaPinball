using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InterfaceGraphique.patron_state
{
    /// <summary>
    /// Etat de selection
    /// </summary>
    class SelectionState : AbstractState
    {
        /// <summary>
        /// Inutile pour la selection puisque aucune action ne doit etre faite sur les objets selectionnees
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        public override void Action(int x, int y)
        { }
    }
}
