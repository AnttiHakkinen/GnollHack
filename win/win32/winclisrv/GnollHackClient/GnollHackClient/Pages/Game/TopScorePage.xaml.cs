﻿using GnollHackCommon;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

using Xamarin.Forms;
using Xamarin.Forms.Xaml;

namespace GnollHackClient.Pages.Game
{
    [XamlCompilation(XamlCompilationOptions.Compile)]
    public partial class TopScorePage : ContentPage
    {
        private string _fileName;
        private ObservableCollection<GHTopScoreItem> _topScores = null;

        public TopScorePage(string fileName)
        {
            InitializeComponent();
            _fileName = fileName;
            Assembly assembly = GetType().GetTypeInfo().Assembly;
            CloseButtonImage.Source = ImageSource.FromResource("GnollHackClient.Assets.button_normal.png", assembly);
            ScoresView.BindingContext = this;
            MainGrid.BindingContext = this;
        }

        public TopScorePage()
        {
            InitializeComponent();
            _fileName = "";
            NoScoresLabel.IsVisible = true;
            ScoresView.IsVisible = false;
            Assembly assembly = GetType().GetTypeInfo().Assembly;
            CloseButtonImage.Source = ImageSource.FromResource("GnollHackClient.Assets.button_normal.png", assembly);
            ScoresView.BindingContext = this;
        }

        private async void CloseButton_Clicked(object sender, EventArgs e)
        {
            await App.Current.MainPage.Navigation.PopModalAsync();
        }

        public bool ReadFile(out string errorMessage)
        {
            string res = "";
            try
            {
                string[] lines = File.ReadAllLines(_fileName);
                List<GHTopScoreItem> newTopScores = new List<GHTopScoreItem>();
                foreach (string line in lines)
                {
                    string[] lineitems = line.Split('\t');
                    GHTopScoreItem tsi = new GHTopScoreItem(this);
                    foreach(string lineitem in lineitems)
                    {
                        tsi.AddXlogLineItemData(lineitem);
                    }
                    newTopScores.Add(tsi);
                }

                /* Sort top scores */
                var q = from s in newTopScores orderby s.Score descending where (App.DeveloperMode || s.Mode == "normal") select s;
                List<GHTopScoreItem> sortedList = q.ToList();
                _topScores = new ObservableCollection<GHTopScoreItem>();
                foreach (GHTopScoreItem sorteditem in sortedList)
                    _topScores.Add(sorteditem);

                int rank = 1;
                int rankadd = 0;
                for (int i = 0; i < _topScores.Count; i++)
                {
                    if (i > 0 && _topScores[i - 1].Score > _topScores[i].Score)
                    {
                        rank += rankadd;
                        rankadd = 1;
                    }
                    else
                        rankadd++;

                    _topScores[i].Rank = rank;
                }

                /* Display in collection view */
                ScoresView.ItemsSource = _topScores;
                NoScoresLabel.IsVisible = (_topScores.Count == 0);
                ScoresView.IsVisible = (_topScores.Count != 0);
            }
            catch (Exception e)
            {
                errorMessage = e.Message;
                return false;
            }
            errorMessage = res;
            return true;
        }

        private double _currentPageWidth = 0;
        private double _currentPageHeight = 0;
        protected override void OnSizeAllocated(double width, double height)
        {
            base.OnSizeAllocated(width, height);
            if (width != _currentPageWidth || height != _currentPageHeight)
            {
                _currentPageWidth = width;
                _currentPageHeight = height;
                if (ScoresView.ItemsSource != null)
                {
                    ScoresView.ItemsSource = null;
                    ScoresView.ItemsSource = _topScores;
                }
            }
        }

        private bool _raceVisible = false;
        public bool IsRaceVisible
        {
            get
            {
                bool newvalue = (Width >= 750);
                if (_raceVisible != newvalue)
                {
                    _raceVisible = newvalue;
                    OnPropertyChanged("IsRaceVisible");
                }
                return _raceVisible;
            }
        }

        private bool _genderVisible = false;
        public bool IsGenderVisible
        {
            get
            {
                bool newvalue = (Width >= 810);
                if (_genderVisible != newvalue)
                {
                    _genderVisible = newvalue;
                    OnPropertyChanged("IsGenderVisible");
                }
                return _genderVisible;
            }
        }

        private bool _alignmentVisible = false;
        public bool IsAlignmentVisible
        {
            get
            {
                bool newvalue = (Width >= 860);
                if (_alignmentVisible != newvalue)
                {
                    _alignmentVisible = newvalue;
                    OnPropertyChanged("IsAlignmentVisible");
                }
                return _alignmentVisible;
            }
        }

        private bool _hpVisible = false;
        public bool IsHPVisible
        {
            get
            {
                bool newvalue = (Width >= 960);
                if (_hpVisible != newvalue)
                {
                    _hpVisible = newvalue;
                    OnPropertyChanged("IsHPVisible");
                }
                return _hpVisible;
            }
        }

        private bool _hpMaxVisible = false;
        public bool IsHPMaxVisible
        {
            get
            {
                bool newvalue = (Width >= 910);
                if (_hpMaxVisible != newvalue)
                {
                    _hpMaxVisible = newvalue;
                    OnPropertyChanged("IsHPMaxVisible");
                }
                return _hpMaxVisible;
            }
        }

        private bool _turnsVisible = false;
        public bool IsTurnsVisible
        {
            get
            {
                bool newvalue = (Width >= 710);
                if (_turnsVisible != newvalue)
                {
                    _turnsVisible = newvalue;
                    OnPropertyChanged("IsTurnsVisible");
                }
                return _turnsVisible;
            }
        }

        private bool _birthDateVisible = false;
        public bool IsBirthDateVisible
        {
            get
            {
                bool newvalue = (Width >= 1045);
                if (_birthDateVisible != newvalue)
                {
                    _birthDateVisible = newvalue;
                    OnPropertyChanged("IsBirthDateVisible");
                }
                return _birthDateVisible;
            }
        }

        private bool _outcomeVisible = false;
        public bool IsOutcomeVisible
        {
            get
            {
                bool newvalue = (Width >= 550);
                if (_outcomeVisible != newvalue)
                {
                    _outcomeVisible = newvalue;
                    OnPropertyChanged("IsOutcomeVisible");
                }
                return _outcomeVisible;
            }
        }

        private double OutComeWidthRequest
        {
            get
            {
                return Math.Max(150, Math.Min(400, Width - 5 - (35 + 170 + 80 + 50 
                    + 50 * (IsRaceVisible ? 1 : 0) + 60 * (IsGenderVisible ? 1 : 0)
                    + 50 * (IsAlignmentVisible ? 1 : 0) + 50 * (IsHPVisible ? 1 : 0) + 50 * (IsHPMaxVisible ? 1 : 0) 
                    + 75 * (IsTurnsVisible ? 1 : 0) + 85 * (IsBirthDateVisible ? 1 : 0) + 25)));
            }
        }

        private double TotalWidthRequest
        {
            get
            {
                return 35 + 170 + 80 + 50 + 50 * (IsRaceVisible ? 1 : 0) + 60 * (IsGenderVisible ? 1 : 0)
                    + 50 * (IsAlignmentVisible ? 1 : 0) + 50 * (IsHPVisible ? 1 : 0) + 50 * (IsHPMaxVisible ? 1 : 0)
                    + 75 * (IsTurnsVisible ? 1 : 0) + 85 * (IsBirthDateVisible ? 1 : 0) + 25 
                    + OutComeWidthRequest * (IsOutcomeVisible ? 1 : 0);
            }
        }
    }
}