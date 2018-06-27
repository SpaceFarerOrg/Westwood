using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Microsoft.Win32;
using System.Windows.Threading;

namespace AnimationEditor
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        AnimationContainer m_animation;
        BitmapImage m_image;
        CroppedBitmap m_croppedImage;
        short m_currentFrame;

        DispatcherTimer m_updateTimer;

        public MainWindow()
        {
            InitializeComponent();

            for (int i = 0; i < (int)EAnimationState.Count; ++i)
            {
                allAnimationStates.Items.Add((EAnimationState)i);
            }

            spriteHeight.IsEnabled = false;
            spriteWidht.IsEnabled = false;
        }

        private void newFile_Click(object sender, RoutedEventArgs e)
        {
            m_animation = new AnimationContainer();

            OpenFileDialog openFileDialog = new OpenFileDialog();

            openFileDialog.Title = "Choose spritesheet";
            openFileDialog.Filter = "*.png|*.png";
            openFileDialog.ShowDialog();

            m_animation.SetSpriteSheet(openFileDialog.FileName);

            if (openFileDialog.CheckFileExists)
            {
                m_image = new BitmapImage(new Uri(m_animation.m_spriteSheet));
                previewWindow.Source = m_image;

                spriteHeight.IsEnabled = true;
                spriteWidht.IsEnabled = true;

            }

        }

        private void spriteWidht_TextChanged(object sender, TextChangedEventArgs e)
        {
            short w = 0;
            if (short.TryParse(spriteWidht.Text, out w))
            {
                m_animation.m_frameW = w;
                UpdateFrame();
            }

        }

        private void spriteHeight_TextChanged(object sender, TextChangedEventArgs e)
        {
            short h = 0;
            if (short.TryParse(spriteWidht.Text, out h))
            {
                m_animation.m_frameH = h;
                UpdateFrame();
            }
        }

        private void UpdateFrame()
        {
            if (m_animation.m_frameW > 0 && m_animation.m_frameH > 0)
            {
                m_croppedImage = new CroppedBitmap(m_image, new Int32Rect(0, 0, m_animation.m_frameW, m_animation.m_frameH));
                previewWindow.Source = m_croppedImage;
            }
        }

        void Update()
        {

        }
    }
}
