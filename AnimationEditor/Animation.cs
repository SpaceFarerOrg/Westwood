using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AnimationEditor
{
    enum EAnimationState
    {
        Idle,
        WalkingLeft,
        WalkingRight,
        WalkingUp,
        WalkingDown,
        Count,
    }

    class AnimationContainer
    {
        public string m_spriteSheet;
        public string m_spriteSheetName;
        List<EAnimationState> m_states;
        public short m_frameW;
        public short m_frameH;

        short m_frameCountX;

        public void SetSpriteSheet(string a_path)
        {
            m_spriteSheet = a_path;

            m_spriteSheetName = a_path.Substring(a_path.LastIndexOf('\\') + 1);
        }

        public bool AddState(EAnimationState a_stateToAdd)
        {
            if (m_states.Contains(a_stateToAdd) == false)
            {
                m_states.Add(a_stateToAdd);
                return true;
            }

            return false;
        }

    }

    struct Frame
    {
        short m_MsToShow;
    }

    class Animation
    {

    }
}
