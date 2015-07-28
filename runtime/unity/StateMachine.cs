using System;
using System.Collections.Generic;

namespace Gree.Ville
{
	class StateMachine
	{
#if UNITY_EDITOR
		private static StateMachine sCurrentMachine;
		private StateMachine mParent;
#endif
		private List<Action> mCurrentStates;
		private List<Action> mNextStates;
		private Action mNextState;
		private bool mYield;
		private bool mExit;
		private string mName;

        public bool DisableLog { get; set; }

		public StateMachine(string name = null)
		{
#if UNITY_EDITOR
			mParent = sCurrentMachine;
#endif
			mName = name;
			Init();
		}

		public void Init()
		{
			mCurrentStates = new List<Action>();
			mNextStates = new List<Action>();
		}

		public void Exec()
		{
#if UNITY_EDITOR
			sCurrentMachine = this;
			try {
#endif
			next();

			Action current = null; // will be set in the first iteration
			foreach (Action state in mCurrentStates) {
				mYield = false;
				mExit = false;
				mNextState = state;

				while (mNextState != null && !mYield && !mExit) {
					current = mNextState;
					mNextState = null;
					current();
					if (mNextState != null && mName != null) {
#if !DISABLE_STATE_MACHINE_LOGGING
                        if (!DisableLog)
                        {
#if UNITY_EDITOR
                            int depth;
                            var path = pathName(out depth);
                            var isDark = UnityEditor.EditorGUIUtility.isProSkin;
                            var h = (((int)path[0] - (int)'A' + 20) % 26) / 26.0f;
                            var s = (isDark) ? 0.4f : 0.7f;
                            var v = Math.Min(depth / 3.0f, 1.0f) * 0.4f + ((isDark) ? 0.6f : 0.3f);
                            Debug.Log("<b><color=" + convertHSV2RGB(h, s, v) + ">[STATE] " + path + " : " + current.Method.Name + " -> " + mNextState.Method.Name + "</color></b>");
#else
                            Debug.Log("[STATE] " + mName + " : " + current.Method.Name + " -> " + mNextState.Method.Name);
#endif
                        }
#endif
					}
				}
				if (mExit) {
					continue;
				}

				mNextStates.Add(mNextState != null ? mNextState : current);
			}
#if UNITY_EDITOR
			} finally {
				sCurrentMachine = mParent;
			}
#endif
		}

#if UNITY_EDITOR
		private string pathName(out int depth)
		{
            depth = 0;
			var s = mName;
			for (var machine = mParent; machine != null; machine = machine.mParent) {
				s = machine.mName + '/' + s;
                depth++;
			}
			return s;
		}
#endif

		private void next()
		{
			List<Action> tmp = mCurrentStates;
			mCurrentStates = mNextStates;
			mNextStates = tmp;
			mNextStates.Clear();
		}

		public void Spawn(Action func)
		{
			mNextStates.Add(func);
		}

		public void SwitchTo(Action func)
		{
			mNextState = func;
			mYield = false;
		}

		public void YieldTo(Action func)
		{
			mNextState = func;
			mYield = true;
		}

		public void Exit()
		{
			mExit = true;
		}

        public bool Exited
        {
            get
            {
                return mExit;
            }
        }

#if UNITY_EDITOR
        // cf. http://ja.wikipedia.org/wiki/HSV%E8%89%B2%E7%A9%BA%E9%96%93#HSV.E3.81.8B.E3.82.89RGB.E3.81.B8.E3.81.AE.E5.A4.89.E6.8F.9B
        public string convertHSV2RGB(float h_, float s_, float v_)
        {
            float r = v_;
            float g = v_;
            float b = v_;
            if (s_ > 0.0f) {
                h_ *= 6.0f;
                int i = (int)h_;
                float f = h_ - (float)i;
                float p = v_ * (1 - s_);
                float q = v_ * (1 - s_ * f);
                float t = v_ * (1 - s_ * (1 - f));
                switch (i) {
                default:
                case 0:
                    r = v_;
                    g = t;
                    b = p;
                    break;
                case 1:
                    r = q;
                    g = v_;
                    b = p;
                    break;
                case 2:
                    r = p;
                    g = v_;
                    b = t;
                    break;
                case 3:
                    r = p;
                    g = q;
                    b = v_;
                    break;
                case 4:
                    r = t;
                    g = p;
                    b = v_;
                    break;
                case 5:
                    r = v_;
                    g = p;
                    b = q;
                    break;
                }
            }
            return "#" + (((int)(r * 255) << 16) | ((int)(g * 255) << 8) | ((int)(b * 255))).ToString("x2");
        }
#endif
	}
}
