﻿using GnollHackCommon;
using Microsoft.AspNetCore.SignalR.Client;
using SkiaSharp;
using SkiaSharp.Views.Forms;
using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

using Xamarin.Forms;
using Xamarin.Forms.Xaml;
using Xamarin.Essentials;
using System.Runtime.InteropServices;
using System.Reflection;
using System.IO;

namespace GnollHackClient.Pages.Game
{
    [XamlCompilation(XamlCompilationOptions.Compile)]
    public partial class GamePage : ContentPage
    {
        private SKColor _cursorDefaultGreen = new SKColor(0, 255, 0);
        private SKRect canvasButtonRect = new SKRect(0, 0, 0, 0);

        Boolean _connectionAttempted = false;
        private HubConnection _connection;
        private string _connection_status = "";
        //private string Message { get { lock (MessageLock) { return TopLineLabel.Text; } } set { lock (MessageLock) { TopLineLabel.Text = value; } } }
        //private object MessageLock = new object();
        //private string _message1 = "";

        private string _message = "";
        private string _message2 = "";
        private string _message3 = "";
        private string _message4 = "";
        private string _message5 = "";
        private int _result = 0;
        private int _result2 = 0;
        private IGnollHackService _gnollHackService;
        public IGnollHackService GnollHackService { get { return _gnollHackService;} }
        private bool _isFirstAppearance = true;
        private Thread _gnhthread;
        private ClientGame _clientGame;
        public ClientGame ClientGame { get { return _clientGame; } }
        private MapData[,] _mapData = new MapData[GHConstants.MapCols, GHConstants.MapRows];
        private object _mapDataLock = new object();
        private int _mapCursorX;
        private int _mapCursorY;
        private int _shownMessageRows = 4;
        public TTYCursorStyle CursorStyle { get; set; }
        public GHGraphicsStyle GraphicsStyle { get; set; }
        private bool _cursorIsOn;
        private bool _showDirections = false;
        private bool _showNumberPad = false;
        private bool showNumberPad { get { return _showNumberPad; } set { _showNumberPad = value; } }
        private MainPage _mainPage;

        private int _clipX;
        private int _clipY;
        public object ClipLock = new object();
        public int ClipX { get { return _clipX; } set { _clipX = value; _mapOffsetX = 0 ; } }
        public int ClipY { get { return _clipY; } set { _clipY = value; _mapOffsetY = 0; } }
        public GHMapMode MapMode { get; set; }
        public bool MapNoClipMode { get; set; }
        public bool MapLookMode { get; set; }
        public bool MapTravelMode { get; set; }


        private float _mapFontSize = 48;
        private object _mapFontSizeLock = new object();
        public float MapFontSize { get { lock (_mapFontSizeLock) { return _mapFontSize; } } set { lock (_mapFontSizeLock) { _mapFontSize = value; } } }
        private float _tileWidth;
        private float _tileHeight;
        private float _mapWidth;
        private float _mapHeight;
        private float _mapFontAscent;
        public object Glyph2TileLock = new object();
        public int[] Glyph2Tile { get; set; }
        public int Glyph2TileSize { get; set; }
        private SKBitmap[] _tileMap = new SKBitmap[GHConstants.MaxTileSheets];
        public SKBitmap[] TileMap { get { return _tileMap; } }
        public int UsedTileSheets { get; set; }
        public int TotalTiles { get; set; }
        public int UnexploredGlyph { get; set; }
        public int NoGlyph { get; set; }
        private int[] _tilesPerRow = new int[GHConstants.MaxTileSheets];
        public int[] TilesPerRow { get { return _tilesPerRow; } }

        public bool EnableWizardMode { get; set; }

        private List<AddContextMenuData> _contextMenuData = new List<AddContextMenuData>();

        public GamePage(MainPage mainPage)
        {
            InitializeComponent();
            _mainPage = mainPage;

            string style = Preferences.Get("CursorStyle", "0");
            int parseint;
            if (int.TryParse(style, out parseint))
            {
                CursorStyle = (TTYCursorStyle)parseint;
            }

            string gstyle = Preferences.Get("GraphicsStyle", "0");
            int gparseint;
            if (int.TryParse(style, out gparseint))
            {
                GraphicsStyle = (GHGraphicsStyle)gparseint;
            }

            ToggleModeButton_Clicked(null, null);
        }

        public async void StartGame()
        {
            //Authenticated
            //App.FmodService.PlayTestSound();

            Assembly assembly = GetType().GetTypeInfo().Assembly;
            using (Stream stream = assembly.GetManifestResourceStream("GnollHackClient.Assets.gnollhack_64x96_transparent_32bits.png"))
            {
                _tileMap[0] = SKBitmap.Decode(stream);
            }

            using (Stream stream = assembly.GetManifestResourceStream("GnollHackClient.Assets.gnollhack_64x96_transparent_32bits-2.png"))
            {
                _tileMap[1] = SKBitmap.Decode(stream);
            }

            InventoryImg.Source = ImageSource.FromResource("GnollHackClient.Assets.Icons.inventory.png");
            SearchImg.Source = ImageSource.FromResource("GnollHackClient.Assets.Icons.search.png");
            WaitImg.Source = ImageSource.FromResource("GnollHackClient.Assets.Icons.wait.png");

            _gnollHackService = DependencyService.Get<IGnollHackService>();
            _gnollHackService.InitializeGnollHack();
            UnexploredGlyph = _gnollHackService.GetUnexploredGlyph();
            NoGlyph = _gnollHackService.GetNoGlyph();

            for (int i = 0; i < GHConstants.MapCols; i++)
            {
                for (int j = 0; j < GHConstants.MapRows; j++)
                {
                    _mapData[i, j] = new MapData();
                    _mapData[i, j].Glyph = UnexploredGlyph;
                    _mapData[i, j].BkGlyph = NoGlyph;
                }
            }

            if (App.IsServerGame)
            {
                _connectionAttempted = true;
                _connection_status = "Not connected";
                _message = "Please wait...";

                if (_connection == null)
                {
                    ConnectToServer();
                }
                else if (_connection.State != HubConnectionState.Connected)
                {
                    await _connection.StopAsync();
                    ConnectToServer();
                }
                else
                {
                    _connection_status = "Connected";
                }

                if (_connection != null)
                {
                    LoginToServer();
                }
            }
            else
            {
                Thread t = new Thread(new ThreadStart(GNHThreadProc));
                _gnhthread = t;
                _gnhthread.Start();
            }

            Device.StartTimer(TimeSpan.FromSeconds(1f / 40), () =>
            {
                canvasView.InvalidateSurface();
                pollRequestQueue();
                return true;
            });

            Device.StartTimer(TimeSpan.FromSeconds(1f / 2), () =>
            {
                if (ClientGame != null)
                    _cursorIsOn = !_cursorIsOn;
                else
                    _cursorIsOn = false;

                return true;
            });


        }

        public void HideLoadingScreen()
        {
            LoadingLabel.IsVisible = false;
            MainGrid.IsVisible = true;
        }

        public void ClearContextMenu()
        {
            ContextGrid.Children.Clear();
            _contextMenuData.Clear();
            ContextGrid.IsVisible = false;
        }
        public void AddContextMenu(AddContextMenuData data)
        {
            _contextMenuData.Add(data);
            string icon_string = "";
            switch((char)data.cmd_def_char)
            {
                case 'e':
                    icon_string = "GnollHackClient.Assets.Icons.eat.png";
                    break;
                case 'l':
                    icon_string = "GnollHackClient.Assets.Icons.loot.png";
                    break;
                case 'p':
                    icon_string = "GnollHackClient.Assets.Icons.pay.png";
                    break;
                case ',':
                    icon_string = "GnollHackClient.Assets.Icons.pickup.png";
                    break;
            }

            if(icon_string != "")
            {
                Image img = new Image();
                img.Source = ImageSource.FromResource(icon_string);
                img.BackgroundColor = Color.Transparent;
                img.HeightRequest = 50;
                img.WidthRequest = 50;
                img.IsVisible = true;
                img.InputTransparent = true;
                img.VerticalOptions = LayoutOptions.Start;
                img.HorizontalOptions = LayoutOptions.Center;

                Label lbl = new Label();
                lbl.Text = data.cmd_text;
                lbl.TextColor = Color.White;
                lbl.FontFamily = "LatoRegular";
                lbl.VerticalOptions = LayoutOptions.End;
                lbl.VerticalTextAlignment = TextAlignment.End;
                lbl.HorizontalOptions = LayoutOptions.Center;
                lbl.HorizontalTextAlignment = TextAlignment.Center;
                lbl.FontSize = 10;
                lbl.BackgroundColor = Color.Transparent;
                lbl.WidthRequest = 50;
                lbl.IsVisible = true;
                lbl.InputTransparent = true;

                Button contextButton = new Button();
                contextButton.Text = "";
                contextButton.HeightRequest = 50;
                contextButton.WidthRequest = 50;
                contextButton.IsVisible = true;
                contextButton.BackgroundColor = Color.Transparent;
                contextButton.HorizontalOptions = LayoutOptions.CenterAndExpand;
                contextButton.VerticalOptions = LayoutOptions.CenterAndExpand;
                contextButton.Clicked += ContextButton_Clicked;

                Grid addgrid = new Grid();
                addgrid.HeightRequest = 60;
                addgrid.WidthRequest = 50;
                addgrid.IsVisible = true;
                addgrid.Children.Add(img);
                addgrid.Children.Add(lbl);
                addgrid.Children.Add(contextButton);

                //int row = ContextGrid.RowDefinitions.Count - 1 - ContextGrid.Children.Count;
                //if (row < 0)
                //    row = 0;
                //Grid.SetRow(contextButton, row);
                ContextGrid.IsVisible = true;
                ContextGrid.Children.Add(addgrid);
            }
            else
            {
                Button contextButton = new Button();
                string str;
                if (data.cmd_def_char >= 32 && data.cmd_def_char < 128)
                    str = ((char)data.cmd_def_char).ToString();
                else if (data.cmd_def_char >= 128)
                    str = "M" + ((char)(data.cmd_def_char - 128)).ToString();
                else if (data.cmd_def_char < 0)
                    str = "M" + ((char)(data.cmd_def_char + 256)).ToString();
                else
                    str = "C" + ((char)(data.cmd_def_char + 64)).ToString();

                contextButton.Text = str;
                contextButton.TextColor = Color.White;
                contextButton.FontFamily = "Immortal";
                contextButton.CornerRadius = 10;
                contextButton.FontSize = 20;
                contextButton.BackgroundColor = Color.DarkBlue;
                contextButton.HeightRequest = 50;
                contextButton.WidthRequest = 50;
                contextButton.IsVisible = true;

                contextButton.Clicked += ContextButton_Clicked;
                //int row = ContextGrid.RowDefinitions.Count - 1 - ContextGrid.Children.Count;
                //if (row < 0)
                //    row = 0;
                //Grid.SetRow(contextButton, row);
                ContextGrid.IsVisible = true;
                ContextGrid.Children.Add(contextButton);
            }
        }

        private void ContextButton_Clicked(object sender, EventArgs e)
        {
            int idx = 0;
            idx = ContextGrid.Children.IndexOf((Xamarin.Forms.View)sender);
            if(idx < 0)
                idx = ContextGrid.Children.IndexOf((Xamarin.Forms.View)((Xamarin.Forms.View)sender).Parent);

            if (idx >= 0 && idx < _contextMenuData.Count)
            {
                int resp = _contextMenuData[idx].cmd_cur_char;
                GenericButton_Clicked(sender, e, resp);
            }
        }

        public int TileSheetIdx(int ntile)
        {
            return (Math.Min(UsedTileSheets - 1, Math.Max(0, (ntile / GHConstants.NumberOfTilesPerSheet))));
        }

        public int TileSheetX(int ntile)
        {
            return (((ntile % GHConstants.NumberOfTilesPerSheet) % _tilesPerRow[TileSheetIdx(ntile)]) * GHConstants.TileWidth);
        }
        public int TileSheetY(int ntile)
        {
            return (((ntile % GHConstants.NumberOfTilesPerSheet) / _tilesPerRow[TileSheetIdx(ntile)]) * GHConstants.TileHeight);
        }

        private /*async*/ void ContentPage_Appearing(object sender, EventArgs e)
        {
            App.BackButtonPressed += BackButtonPressed;

            if(_isFirstAppearance)
            {
                _isFirstAppearance = false;

                //int res = 0; // _gnollHackService.Test1();
            }
        }

        protected void GNHThreadProc()
        {
            _clientGame = new ClientGame(this, EnableWizardMode);
            _gnollHackService.StartGnollHack(_clientGame);
        }

        private void pollRequestQueue()
        {
            if(_clientGame != null)
            {
                GHRequest req;
                ConcurrentQueue<GHRequest> queue;
                if (ClientGame.RequestDictionary.TryGetValue(_clientGame, out queue))
                {
                    while (queue.TryDequeue(out req))
                    {
                        switch (req.RequestType)
                        {
                            case GHRequestType.PrintHistory:
                                PrintHistory(req.MessageHistory);
                                break;
                            case GHRequestType.PrintTopLine:
                                PrintTopLine(req.RequestString, req.RequestStringAttributes);
                                break;
                            case GHRequestType.ShowYnResponses:
                                ShowYnResponses(req.RequestString, req.Responses);
                                break;
                            case GHRequestType.HideYnResponses:
                                HideYnResponses();
                                break;
                            case GHRequestType.ShowDirections:
                                ShowDirections();
                                break;
                            case GHRequestType.HideDirections:
                                HideDirections();
                                break;
                            case GHRequestType.GetChar:
                                GetChar();
                                break;
                            case GHRequestType.AskName:
                                AskName();
                                break;
                            case GHRequestType.GetLine:
                                GetLine(req.RequestString);
                                break;
                            case GHRequestType.ReturnToMainMenu:
                                ClearMap();
                                _clientGame = null;
                                ReturnToMainMenu();
                                break;
                            case GHRequestType.ShowMenuPage:
                                ShowMenuPage(req.RequestMenuInfo != null ? req.RequestMenuInfo : new GHMenuInfo(), req.RequestingGHWindow);
                                break;
                            case GHRequestType.CreateWindowView:
                                CreateWindowView(req.RequestInt);
                                break;
                            case GHRequestType.DestroyWindowView:
                                DestroyWindowView(req.RequestInt);
                                break;
                            case GHRequestType.ClearWindowView:
                                ClearWindowView(req.RequestInt);
                                break;
                            case GHRequestType.DisplayWindowView:
                                DisplayWindowView(req.RequestInt, req.RequestPutStrItems);
                                break;
                            case GHRequestType.HideLoadingScreen:
                                HideLoadingScreen();
                                break;
                            case GHRequestType.ClearContextMenu:
                                ClearContextMenu();
                                break;
                            case GHRequestType.AddContextMenu:
                                AddContextMenu(req.ContextMenuData);
                                break;
                        }
                    }
                }
            }
        }

        private void CreateWindowView(int winid)
        {

        }

        private void DestroyWindowView(int winid)
        {

        }

        private void ClearWindowView(int winid)
        {

        }

        private void DisplayWindowView(int winid, List<GHPutStrItem> strs)
        {
            ShowWindowPage(strs);
        }
        private async void ShowWindowPage(List<GHPutStrItem> strs)
        {
            var cpage = new GHTextPage(this, strs);
            await App.Current.MainPage.Navigation.PushModalAsync(cpage);
        }

        private void PrintTopLine(string str, uint attributes)
        {
            /*
            TopLineLabel.Text = str;
            switch(attributes)
            {
                case 0:
                    TopLineLabel.FontAttributes = FontAttributes.None;
                    break;
                case 1:
                    TopLineLabel.FontAttributes = FontAttributes.Bold;
                    break;
            }
            */
        }

        private string CurrentYnResponses;
        private void ShowYnResponses(string question, string responses)
        {
            CurrentYnResponses = responses;
            QuestionLabel.Text = question;
            if (responses.Length == 0)
                return;
            else if(responses.Length == 1)
            {
                SecondButton.Text = responses;
                ZeroButton.IsVisible = false;
                FirstButton.IsVisible = false;
                SecondButton.IsVisible = true;
                ThirdButton.IsVisible = false;
                FourthButton.IsVisible = false;
            }
            else if(responses.Length == 2)
            {
                ZeroButton.IsVisible = false;
                FirstButton.IsVisible = true;
                SecondButton.IsVisible = true;
                ThirdButton.IsVisible = false;
                FourthButton.IsVisible = false;
                FirstButton.Text = responses.Substring(0, 1);
                SecondButton.Text = responses.Substring(1, 1);
            }
            else if (responses.Length == 3)
            {
                ZeroButton.IsVisible = false;
                FirstButton.IsVisible = true;
                SecondButton.IsVisible = true;
                ThirdButton.IsVisible = true;
                FourthButton.IsVisible = false;
                FirstButton.Text = responses.Substring(0, 1);
                SecondButton.Text = responses.Substring(1, 1);
                ThirdButton.Text = responses.Substring(2, 1);
            }
            else
            {
                Button[] btnList = { ZeroButton, FirstButton, SecondButton, ThirdButton, FourthButton };


                for (int i = 0; i < 4; i++)
                {
                    if (i < responses.Length)
                    {
                        btnList[i].Text = responses.Substring(i, 1);
                        btnList[i].IsVisible = true;
                    }
                    else
                    {
                        btnList[i].Text = "?";
                        btnList[i].IsVisible = false;
                    }
                }
            }

            YnGrid.IsVisible = true;
        }

        private void HideYnResponses()
        {
            YnGrid.IsVisible = false;
        }
        private void ShowDirections()
        {
            _showDirections = true;
            showNumberPad = false;
        }
        private void HideDirections()
        {
            _showDirections = false;
            showNumberPad = false;
        }
        public void ShowNumberPad()
        {
            if(!_showDirections)
                showNumberPad = true;
        }

        private object msgHistoryLock = new object();
        private List<GHMsgHistoryItem> _msgHistory = null;
        private void PrintHistory(List<GHMsgHistoryItem> msgHistory)
        {
            lock(msgHistoryLock)
            {
                _msgHistory = msgHistory;
            }
            /*
            messagehistoryview.itemssource = msghistory;
            if (msghistory.count > 0)
                messagehistoryview.scrollto(msghistory.count - 1, -1, scrolltoposition.end, false);
            */
        }

        private async void AskName()
        {
            var namePage = new NamePage(this);
            await App.Current.MainPage.Navigation.PushModalAsync(namePage);
        }
        private async void GetLine(string query)
        {
            var getLinePage = new GetLinePage(this, query);
            await App.Current.MainPage.Navigation.PushModalAsync(getLinePage);
        }

        private void GetChar()
        {
            // Set focus to GameViewPage
        }
        private async void ReturnToMainMenu()
        {
            if(!App.IsServerGame)
                _mainPage.HideLocalGameButton();
    
            await App.Current.MainPage.Navigation.PopModalAsync();
            if (App.IsServerGame)
            {
                await App.Current.MainPage.Navigation.PopAsync(); //Login
            }
        }
        private async void ShowMenuPage(GHMenuInfo menuinfo, GHWindow ghwindow)
        {
            var menuPage = new GHMenuPage(this, ghwindow);
            menuPage.SelectionHow = menuinfo.SelectionHow;
            menuPage.Header = menuinfo.Header;
            if (menuinfo != null)
                menuPage.MenuItems.AddRange(menuinfo.MenuItems);
            menuPage.Process();
            await App.Current.MainPage.Navigation.PushModalAsync(menuPage);
        }
        private async Task<bool> BackButtonPressed(object sender, EventArgs e)
        {
            var menu = new GameMenuPage(this);
            await App.Current.MainPage.Navigation.PushModalAsync(menu);

            return false;
        }

        private void ContentPage_Disappearing(object sender, EventArgs e)
        {
            App.BackButtonPressed -= BackButtonPressed;
        }

        private void canvasView_PaintSurface(object sender, SKPaintSurfaceEventArgs e)
        {
            SKImageInfo info = e.Info;
            SKSurface surface = e.Surface;
            SKCanvas canvas = surface.Canvas;

            string str = "";

            canvas.Clear(SKColors.Black);

            float x = info.Width;
            float y = info.Height;

            SKPaint textPaint = new SKPaint
            {
                Color = SKColors.White
            };
            textPaint.Typeface = App.DiabloTypeface;

            // Adjust TextSize property so text is 90% of screen width
            float textWidth = textPaint.MeasureText(str);
            textPaint.TextSize = 0.65f * info.Width * textPaint.TextSize / textWidth;

            // Find the text bounds
            SKRect textBounds = new SKRect();
            textPaint.MeasureText(str, ref textBounds);

            var xText = 10;
            var yText = 0;
            string additional_info = "";
            if (_connection == null && _connectionAttempted)
                additional_info = ", no _connection";
            else if (_connection == null)
            {
                /* Do nothing */
            }
            else if (_connection.State == HubConnectionState.Connected)
                additional_info = ", connected";
            else if (_connection.State == HubConnectionState.Connecting)
                additional_info = ", connecting";
            else if (_connection.State == HubConnectionState.Disconnected)
                additional_info = ", disconnected";
            else if (_connection.State == HubConnectionState.Reconnecting)
                additional_info = ", reconnecting";

            str = _connection_status + additional_info;
            textPaint.TextSize = 36;
            yText = yText + 50;
            canvas.DrawText(str, xText, yText, textPaint);

            str = _message;
            textPaint.TextSize = 36;
            yText = yText + 50;
            canvas.DrawText(str, xText, yText, textPaint);

            str = _message2;
            textPaint.TextSize = 36;
            yText = yText + 50;
            canvas.DrawText(str, xText, yText, textPaint);

            if (_result != 0)
            {
                str = _result.ToString();
                yText = yText + 50;
                canvas.DrawText(str, xText, yText, textPaint);
            }

            if (_result2 != 0)
            {
                str = _result2.ToString();
                yText = yText + 50;
                canvas.DrawText(str, xText, yText, textPaint);
            }

            str = _message3;
            yText = yText + 50;
            canvas.DrawText(str, xText, yText, textPaint);

            str = _message4;
            yText = yText + 50;
            canvas.DrawText(str, xText, yText, textPaint);

            str = _message5;
            yText = yText + 50;
            canvas.DrawText(str, xText, yText, textPaint);


            /* Map */
            textPaint.Typeface = App.DejaVuSansMonoTypeface;
            textPaint.TextSize = MapFontSize;
            float canvaswidth = canvasView.CanvasSize.Width;
            float canvasheight = canvasView.CanvasSize.Height;
            float width = textPaint.FontMetrics.AverageCharacterWidth;
            float height = textPaint.FontMetrics.Descent - textPaint.FontMetrics.Ascent;

            if (GraphicsStyle == GHGraphicsStyle.Tiles)
            {
                width = GHConstants.TileWidth * MapFontSize / 48;
                height = GHConstants.TileHeight * MapFontSize / 48;
            }

            float mapwidth = width * (GHConstants.MapCols -1);
            float mapheight = height * (GHConstants.MapRows);

            _tileWidth = width;
            _tileHeight = height;
            _mapWidth = mapwidth;
            _mapHeight = mapheight;
            _mapFontAscent = textPaint.FontMetrics.Ascent;

            int startX = 1;
            int endX = GHConstants.MapCols - 1;
            int startY = 0;
            int endY = GHConstants.MapRows - 1;

            float offsetX = (canvaswidth - mapwidth) / 2;
            float offsetY = (canvasheight - mapheight) / 2;

            lock (ClipLock)
            {
                if (ClipX > 0 && (mapwidth > canvaswidth || mapheight > canvasheight))
                {
                    offsetX -= (ClipX - (GHConstants.MapCols - 1) / 2) * width;
                    offsetY -= (ClipY - GHConstants.MapRows / 2) * height;
                }
            }

            float tx = 0, ty = 0;
            float startx = 0, starty = 0;
            if(_clientGame != null)
            {
                lock (_clientGame.WindowsLock)
                {
                    if (_clientGame.Windows[_clientGame.MapWindowId] != null)
                    {
                        startx = _clientGame.Windows[_clientGame.MapWindowId].Left;
                        starty = _clientGame.Windows[_clientGame.MapWindowId].Top;
                    }
                }
            }

            lock(Glyph2TileLock)
            {
                lock (_mapDataLock)
                {
                    if (GraphicsStyle == GHGraphicsStyle.ASCII)
                    {
                        for (int mapx = startX; mapx <= endX; mapx++)
                        {
                            for (int mapy = startY; mapy <= endY; mapy++)
                            {
                                if (_mapData[mapx, mapy].Symbol != null && _mapData[mapx, mapy].Symbol != "")
                                {
                                    str = _mapData[mapx, mapy].Symbol;
                                    textPaint.Color = _mapData[mapx, mapy].Color;
                                    tx = (startX + offsetX + _mapOffsetX + width * (float)mapx);
                                    ty = (startY + offsetY + _mapOffsetY + height * (float)mapy);
                                    if (CursorStyle == TTYCursorStyle.GreenBlock && _mapCursorX == mapx && _mapCursorY == mapy)
                                    {
                                        textPaint.Style = SKPaintStyle.Fill;
                                        textPaint.Color = _cursorDefaultGreen;
                                        SKRect winRect = new SKRect(tx, ty + textPaint.FontMetrics.Ascent, tx + width, ty + textPaint.FontMetrics.Ascent + height);
                                        canvas.DrawRect(winRect, textPaint);
                                        textPaint.Color = SKColors.Black;
                                    }
                                    else if ((_mapData[mapx, mapy].Special & (uint)MapSpecial.Pet) != 0)
                                    {
                                        textPaint.Style = SKPaintStyle.Fill;
                                        SKRect winRect = new SKRect(tx, ty + textPaint.FontMetrics.Ascent, tx + width, ty + textPaint.FontMetrics.Ascent + height);
                                        canvas.DrawRect(winRect, textPaint);
                                        textPaint.Color = SKColors.Black;
                                    }

                                    canvas.DrawText(str, tx, ty, textPaint);

                                    if ((_mapData[mapx, mapy].Special & (uint)MapSpecial.Peaceful) != 0)
                                    {
                                        canvas.DrawText("_", tx, ty, textPaint);
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        if (Glyph2Tile != null && _tilesPerRow[0] > 0 && UsedTileSheets > 0)
                        {
                            for (int mapx = startX; mapx <= endX; mapx++)
                            {
                                for (int mapy = startY; mapy <= endY; mapy++)
                                {
                                    for (int layer = 0; layer < 2; layer++)
                                    {
                                        int signed_glyph = layer == 0 ? _mapData[mapx, mapy].BkGlyph : _mapData[mapx, mapy].Glyph;
                                        int glyph = Math.Abs(signed_glyph);
                                        bool hflip = (signed_glyph < 0);

                                        if (glyph == 0 && layer == 0)
                                            continue;

                                        if (glyph < Glyph2Tile.Length)
                                        {
                                            int ntile = Glyph2Tile[glyph];
                                            int sheet_idx = TileSheetIdx(ntile);
                                            int tile_x = TileSheetX(ntile);
                                            int tile_y = TileSheetY(ntile);

                                            SKRect sourcerect = new SKRect(tile_x, tile_y, tile_x + GHConstants.TileWidth, tile_y + GHConstants.TileHeight);

                                            tx = (startX + offsetX + _mapOffsetX + width * (float)mapx);
                                            ty = (startY + offsetY + _mapOffsetY + _mapFontAscent + height * (float)mapy);

                                            SKRect targetrect = new SKRect(tx, ty, tx + width, ty + height);

                                            canvas.DrawBitmap(TileMap[sheet_idx], sourcerect, targetrect);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                /* Cursor */
                if (GraphicsStyle == GHGraphicsStyle.ASCII && CursorStyle == TTYCursorStyle.BlinkingUnderline && _cursorIsOn && _mapCursorX >= 1 && _mapCursorY >= 0)
                {
                    int cx = _mapCursorX, cy = _mapCursorY;
                    str = "_";
                    textPaint.Color = SKColors.White;
                    tx = (startX + offsetX + _mapOffsetX + width * (float)cx);
                    ty = (startY + offsetY + _mapOffsetY + height * (float)cy);
                    canvas.DrawText(str, tx, ty, textPaint);
                }
            }

            canvasButtonRect.Top = 0; /* Maybe overrwritten below */
            canvasButtonRect.Bottom = canvasheight; /* Maybe overrwritten below */
            if (_clientGame != null)
            {
                /* Window strings */
                lock (_clientGame.WindowsLock)
                {
                    for (int i = 0; _clientGame.Windows[i] != null && i < GHConstants.MaxGHWindows; i++)
                    {
                        if (_clientGame.Windows[i].Visible && (
                            _clientGame.Windows[i].WindowPrintStyle == GHWindowPrintLocations.PrintToMap
                            || _clientGame.Windows[i].WindowPrintStyle == GHWindowPrintLocations.RawPrint))
                        {
                            textPaint.Typeface = _clientGame.Windows[i].Typeface;
                            textPaint.TextSize = _clientGame.Windows[i].TextSize;
                            textPaint.Color = _clientGame.Windows[i].TextColor;
                            width = textPaint.FontMetrics.AverageCharacterWidth;
                            height = textPaint.FontSpacing; // textPaint.FontMetrics.Descent - textPaint.FontMetrics.Ascent;

                            if(_clientGame.Windows[i].AutoPlacement)
                            {
                                if (_clientGame.Windows[i].WindowType == GHWinType.Message)
                                {
                                    float newleft = 0;
                                    float newtop = canvasheight - height * _shownMessageRows - 30;
                                    _clientGame.Windows[i].Left = newleft;
                                    _clientGame.Windows[i].Top = newtop;
                                }
                                else if (_clientGame.Windows[i].WindowType == GHWinType.Here)
                                {
                                    float newleft = 0;
                                    float messagetop = _clientGame.Windows[_clientGame.MessageWindowId].Top;
                                    float newtop = messagetop - _clientGame.Windows[i].Height - 30;
                                    _clientGame.Windows[i].Left = newleft;
                                    _clientGame.Windows[i].Top = newtop;
                                }
                            }

                            SKRect winRect = new SKRect(_clientGame.Windows[i].Left, _clientGame.Windows[i].Top,
                                _clientGame.Windows[i].Right,
                                _clientGame.Windows[i].Bottom);

                            if(_clientGame.Windows[i].CenterHorizontally && winRect.Right - winRect.Left < canvaswidth)
                            {
                                float newleft = (canvaswidth - (winRect.Right - winRect.Left)) / 2;
                                float addition = newleft - winRect.Left;
                                winRect.Left += addition;
                                winRect.Right += addition;
                            }

                            SKPaint winPaint = new SKPaint
                            {
                                Color = _clientGame.Windows[i].BackgroundColor,
                                Style = SKPaintStyle.Fill
                            };

                            if(winPaint.Color != SKColors.Transparent)
                                canvas.DrawRect(winRect, winPaint);

                            if(i == _clientGame.StatusWindowId)
                                canvasButtonRect.Top = winRect.Bottom;
                            else if (i == _clientGame.MessageWindowId)
                                canvasButtonRect.Bottom = winRect.Top;

                            if (_clientGame.Windows[i].WindowType != GHWinType.Message)
                            {
                                lock (_clientGame.Windows[i].PutStrsLock)
                                {
                                    int j = 0;
                                    foreach (GHPutStrItem putstritem in _clientGame.Windows[i].PutStrs)
                                    {
                                        int pos = 0;
                                        float xpos = 0;
                                        float totwidth = 0;
                                        foreach (GHPutStrInstructions instr in putstritem.InstructionList)
                                        {
                                            if (putstritem.Text == null)
                                                str = "";
                                            else if (pos + instr.PrintLength <= putstritem.Text.Length)
                                                str = putstritem.Text.Substring(pos, instr.PrintLength);
                                            else if (putstritem.Text.Length - pos > 0)
                                                str = putstritem.Text.Substring(pos, putstritem.Text.Length - pos);
                                            else
                                                str = "";
                                            pos += str.Length;
                                            textPaint.Color = NHColor2SKColor(instr.Color < (int)nhcolor.CLR_MAX ? (nhcolor)instr.Color : nhcolor.CLR_WHITE);
                                            totwidth = textPaint.MeasureText(str, ref textBounds);

                                            /* attributes */
                                            tx = xpos + winRect.Left + _clientGame.Windows[i].Padding.Left;
                                            ty = winRect.Top + _clientGame.Windows[i].Padding.Top - textPaint.FontMetrics.Ascent + j * height;
                                            canvas.DrawText(str, tx, ty, textPaint);
                                            textPaint.Style = SKPaintStyle.Stroke;
                                            textPaint.StrokeWidth = _clientGame.Windows[i].StrokeWidth;
                                            textPaint.Color = SKColors.Black;
                                            canvas.DrawText(str, tx, ty, textPaint);
                                            textPaint.Style = SKPaintStyle.Fill;
                                            xpos += totwidth;
                                        }
                                        j++;
                                    }
                                }
                            }

                            if (_clientGame.Windows[i].WindowType == GHWinType.Message)
                            {
                                lock (msgHistoryLock)
                                {
                                    if(_msgHistory != null)
                                    {
                                        int j = _shownMessageRows - 1, idx;
                                        for (idx = _msgHistory.Count - 1; idx >= 0 && j >= 0; idx--)
                                        {
                                            GHMsgHistoryItem msgHistoryItem = _msgHistory[idx];
                                            string longLine = msgHistoryItem.Text;
                                            SKColor printColor = NHColor2SKColor(msgHistoryItem.NHColor < nhcolor.CLR_MAX ? msgHistoryItem.NHColor : nhcolor.CLR_WHITE);

                                            textPaint.Style = SKPaintStyle.Fill;
                                            textPaint.StrokeWidth = 0;
                                            textPaint.Color = printColor;
                                            /* attributes */

                                            float lineLengthLimit = 0.8f * canvaswidth;
                                            var wrappedLines = new List<string>();
                                            var lineLength = 0.0f;
                                            var line = "";
                                            foreach (var word in longLine.Split(' '))
                                            {
                                                var wordWithSpace = word + " ";
                                                var wordWithSpaceLength = textPaint.MeasureText(wordWithSpace);
                                                if (lineLength + wordWithSpaceLength > lineLengthLimit)
                                                {
                                                    wrappedLines.Add(line);
                                                    line = "" + wordWithSpace;
                                                    lineLength = wordWithSpaceLength;
                                                }
                                                else
                                                {
                                                    line += wordWithSpace;
                                                    lineLength += wordWithSpaceLength;
                                                }
                                            }
                                            wrappedLines.Add(line);

                                            int lineidx;
                                            for (lineidx = 0; lineidx < wrappedLines.Count; lineidx++)
                                            {
                                                string wrappedLine = wrappedLines[lineidx];
                                                int window_row_idx = j + lineidx - wrappedLines.Count + 1;
                                                if (window_row_idx < 0)
                                                    continue;
                                                tx = winRect.Left + _clientGame.Windows[i].Padding.Left;
                                                ty = winRect.Top + _clientGame.Windows[i].Padding.Top - textPaint.FontMetrics.Ascent + window_row_idx * height;
                                                canvas.DrawText(wrappedLine, tx, ty, textPaint);
                                                textPaint.Style = SKPaintStyle.Stroke;
                                                textPaint.StrokeWidth = _clientGame.Windows[i].StrokeWidth;
                                                textPaint.Color = SKColors.Black;
                                                canvas.DrawText(wrappedLine, tx, ty, textPaint);
                                                textPaint.Style = SKPaintStyle.Fill;
                                                textPaint.StrokeWidth = 0;
                                                textPaint.Color = printColor;
                                            }
                                            j -= wrappedLines.Count;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

            }

            canvasButtonRect.Right = canvaswidth * (float)(0.8);
            canvasButtonRect.Left = canvaswidth * (float)(0.2);

            if (_showDirections || showNumberPad)
            {
                textPaint.Color = new SKColor(255, 255, 255, 128);
                textPaint.Typeface = App.DejaVuSansMonoTypeface;
                textPaint.TextSize = showNumberPad ? 250 : 400;
                for (int i = 0; i <= 9;i++)
                {
                    switch (i)
                    {
                        case 0:
                            if (_showDirections)
                                str = "\u2190";
                            else
                                str = "4";
                            tx = canvasButtonRect.Left + canvasButtonRect.Width * 0.15f - textPaint.FontMetrics.AverageCharacterWidth / 2;
                            ty = canvasButtonRect.Top + canvasButtonRect.Height / 2 + textPaint.FontMetrics.Descent;
                            break;
                        case 1:
                            if (_showDirections)
                                str = "\u2191";
                            else
                                str = "8";
                            tx = canvasButtonRect.Left + canvasButtonRect.Width / 2 - textPaint.FontMetrics.AverageCharacterWidth / 2;
                            ty = canvasButtonRect.Top + canvasButtonRect.Height * 0.15f + textPaint.FontMetrics.Descent;
                            break;
                        case 2:
                            if (_showDirections)
                                str = "\u2192";
                            else
                                str = "6";
                            tx = canvasButtonRect.Left + canvasButtonRect.Width * 0.85f - textPaint.FontMetrics.AverageCharacterWidth / 2;
                            ty = canvasButtonRect.Top + canvasButtonRect.Height / 2 + textPaint.FontMetrics.Descent;
                            break;
                        case 3:
                            if (_showDirections)
                                str = "\u2193";
                            else
                                str = "2";
                            tx = canvasButtonRect.Left + canvasButtonRect.Width / 2 - textPaint.FontMetrics.AverageCharacterWidth / 2;
                            ty = canvasButtonRect.Top + canvasButtonRect.Height * 0.85f + textPaint.FontMetrics.Descent;
                            break;
                        case 4:
                            if (_showDirections)
                                str = "\u2196";
                            else
                                str = "7";
                            tx = canvasButtonRect.Left + canvasButtonRect.Width * 0.15f - textPaint.FontMetrics.AverageCharacterWidth / 2;
                            ty = canvasButtonRect.Top + canvasButtonRect.Height * 0.15f + textPaint.FontMetrics.Descent;
                            break;
                        case 5:
                            if (_showDirections)
                                str = "";
                            else
                                str = "5";
                            tx = canvasButtonRect.Left + canvasButtonRect.Width / 2 - textPaint.FontMetrics.AverageCharacterWidth / 2;
                            ty = canvasButtonRect.Top + canvasButtonRect.Height / 2 + textPaint.FontMetrics.Descent;
                            break;
                        case 6:
                            if (_showDirections)
                                str = "\u2197";
                            else
                                str = "9";
                            tx = canvasButtonRect.Left + canvasButtonRect.Width * 0.85f - textPaint.FontMetrics.AverageCharacterWidth / 2;
                            ty = canvasButtonRect.Top + canvasButtonRect.Height * 0.15f + textPaint.FontMetrics.Descent;
                            break;
                        case 7:
                            if (_showDirections)
                                str = "\u2198";
                            else
                                str = "3";
                            tx = canvasButtonRect.Left + canvasButtonRect.Width * 0.85f - textPaint.FontMetrics.AverageCharacterWidth / 2;
                            ty = canvasButtonRect.Top + canvasButtonRect.Height * 0.85f + textPaint.FontMetrics.Descent;
                            break;
                        case 8:
                            if (_showDirections)
                                str = "\u2199";
                            else
                                str = "1";
                            tx = canvasButtonRect.Left + canvasButtonRect.Width * 0.15f - textPaint.FontMetrics.AverageCharacterWidth / 2;
                            ty = canvasButtonRect.Top + canvasButtonRect.Height * 0.85f + textPaint.FontMetrics.Descent;
                            break;
                        case 9:
                            if (_showDirections)
                                continue;
                            else
                                str = "0";
                            tx = 0 + canvasButtonRect.Left / 2 - textPaint.FontMetrics.AverageCharacterWidth / 2;
                            ty = canvasButtonRect.Top + canvasButtonRect.Height * 0.15f + textPaint.FontMetrics.Descent;
                            textPaint.TextSize = Math.Max(10.0f, textPaint.TextSize * Math.Min(1.0f, canvasButtonRect.Left / (canvasButtonRect.Width * 0.3f)));
                            break;
                    }
                    canvas.DrawText(str, tx, ty, textPaint);

                }
            }



            /* RawPrint */
            /*
            lock(MessageLock)
            {
                str = Message;
            }

            textPaint.Typeface = App.DiabloTypeface;
            textPaint.TextSize = 36;
            textPaint.Color = SKColors.White;
            yText = 50;
            canvas.DrawText(str, xText, yText, textPaint);
            */

        }

        private double _currentPageWidth = 0;
        private double _currentPageHeight = 0;

        protected override void OnSizeAllocated(double width, double height)
        {
            base.OnSizeAllocated(width, height);
            if(width != _currentPageWidth || height != _currentPageHeight)
            {
                _currentPageWidth = width;
                _currentPageHeight = height;

                if (width > height)
                {
                    ButtonRowStack.Orientation = StackOrientation.Horizontal;
                    ModeLayout.Orientation = StackOrientation.Horizontal;
                }
                else
                {
                    ButtonRowStack.Orientation = StackOrientation.Vertical;
                    ModeLayout.Orientation = StackOrientation.Vertical;
                }
            }
        }

        protected void ConnectToServer()
        {
            if (App.AuthenticationCookie == null)
            {
                throw new Exception("AuthenticationCookie is null");
            }

            if (App.SelectedServer == null)
            {
                throw new Exception("SelectedServer is null");
            }

            _connection = new HubConnectionBuilder().WithUrl(App.SelectedServer.Url + "gnollhack", options =>
            {
                options.Cookies.Add(App.AuthenticationCookie);
            }).Build();

            if (_connection != null)
            {
                _connection_status = "Connection attempted";
            }
            else
            {
                _connection_status = "Connection attempt failed";
            }

            _connection.Closed += async (error) =>
            {
                _connection_status = "Connection closed";
                await Task.Delay(new Random().Next(0, 5) * 1000);
                await _connection.StartAsync();
            };

            _connection.On<string, string>("ReceiveMessage", (user, message) =>
            {
                _message = message;
            });

            _connection.On<int>("CalcResult", (result) =>
            {
                _result = result;
            });

            _connection.On<string, string>("LoginMessage", (user, message) =>
            {
                _message2 = message;
            });

            _connection.On<int>("AddNewGameResult", (result) =>
            {
                _message3 = "New Game Added: " + result;
                _clientGame = new ClientGame(this, EnableWizardMode);
            });

            _connection.On<bool>("GameAliveResult", (result) =>
            {
                _message4 = "Game Alive: " + result.ToString();
            });
            _connection.On<int, int>("Client_ExitHack", (hash, status) =>
            {
                _message5 = "ExitHack: Hash: " + hash + ", Status: " + status;
            });
            _connection.On<int>("Client_PlayerSelection", (hash) =>
            {
                _message5 = "PlayerSelection: Hash: " + hash;
            });
            _connection.On<GHCommandFromServer>("CommandFromServer", (command) =>
            {
                _message5 = "CommandFromServer: " + command.CommandName + ", GUID: " + command.Id.ToString();
            });
            _connection.On<Guid, int>("ResponseFromClientResult", (guid, result) =>
            {
                _message5 = "ResponseFromClientResult: " + result + ", GUID: " + guid;
            });
        }

        protected async void LoginToServer()
        {
            try
            {
                await _connection.StartAsync();

                await _connection.InvokeAsync("SendMessage",
                    "user", "My message");

                await _connection.InvokeAsync("DoCalc");

                await _connection.InvokeAsync("AddNewServerGame");
            }
            catch (Exception ex)
            {
                //Error
            }
        }

        private Dictionary<long, TouchEntry> TouchDictionary = new Dictionary<long, TouchEntry>();
        private float _mapOffsetX = 0;
        private float _mapOffsetY = 0;
        private bool _touchMoved = false;

        private void canvasView_Touch(object sender, SKTouchEventArgs e)
        {
            if (_clientGame != null)
            {
                switch (e?.ActionType)
                {
                    case SKTouchAction.Entered:
                        break;
                    case SKTouchAction.Pressed:
                        if (TouchDictionary.ContainsKey(e.Id))
                            TouchDictionary[e.Id] = new TouchEntry(e.Location, DateTime.Now);
                        else
                            TouchDictionary.Add(e.Id, new TouchEntry(e.Location, DateTime.Now));
                        
                        if (TouchDictionary.Count > 1)
                            _touchMoved = true;

                        e.Handled = true;
                        break;
                    case SKTouchAction.Moved:
                        {
                            TouchEntry entry;
                            bool res = TouchDictionary.TryGetValue(e.Id, out entry);
                            if (res)
                            {
                                SKPoint anchor = entry.Location;

                                float diffX = e.Location.X - anchor.X;
                                float diffY = e.Location.Y - anchor.Y;
                                float dist = (float)Math.Sqrt((Math.Pow(diffX, 2) + Math.Pow(diffY, 2)));

                                if (TouchDictionary.Count == 1 &&
                                    (
                                        dist > 25 ||
                                        (DateTime.Now.Ticks - entry.PressTime.Ticks) / TimeSpan.TicksPerMillisecond > GHConstants.MoveOrPressTimeThreshold)
                                    )
                                {
                                    /* Just one finger => Move the map */
                                    if (diffX != 0 || diffY != 0)
                                    {
                                        _mapOffsetX += diffX;
                                        _mapOffsetY += diffY;
                                        if (_mapWidth > 0 && Math.Abs(_mapOffsetX) > 10 * _mapWidth)
                                        {
                                            _mapOffsetX = 10 * _mapWidth * Math.Sign(_mapOffsetX);
                                        }
                                        if (_mapHeight > 0 && Math.Abs(_mapOffsetY) > 10 * _mapHeight)
                                        {
                                            _mapOffsetY = 10 * _mapHeight * Math.Sign(_mapOffsetY);
                                        }
                                        TouchDictionary[e.Id].Location = e.Location;
                                        _touchMoved = true;
                                    }
                                }
                                else if (TouchDictionary.Count == 2)
                                {
                                    SKPoint prevloc = TouchDictionary[e.Id].Location;
                                    SKPoint curloc = e.Location;
                                    SKPoint otherloc;

                                    Dictionary<long, TouchEntry>.KeyCollection keys = TouchDictionary.Keys;
                                    long other_key = 0;
                                    foreach (long key in keys)
                                    {
                                        if (key != e.Id)
                                        {
                                            other_key = key;
                                            break;
                                        }
                                    }

                                    if (other_key != 0)
                                    {
                                        otherloc = TouchDictionary[other_key].Location;
                                        float prevdist = (float)Math.Sqrt((Math.Pow((double)otherloc.X - (double)prevloc.X, 2) + Math.Pow((double)otherloc.Y - (double)prevloc.Y, 2)));
                                        float curdist = (float)Math.Sqrt((Math.Pow((double)otherloc.X - (double)curloc.X, 2) + Math.Pow((double)otherloc.Y - (double)curloc.Y, 2)));
                                        if (prevdist > 0 && curdist > 0)
                                        {
                                            float ratio = curdist / prevdist;
                                            float curfontsize = MapFontSize;
                                            float newfontsize = curfontsize * ratio;
                                            if (newfontsize > 500)
                                                newfontsize = 500;
                                            if (newfontsize < 4)
                                                newfontsize = 4;
                                            MapFontSize = newfontsize;
                                        }
                                    }

                                    TouchDictionary[e.Id].Location = e.Location;
                                    _touchMoved = true;
                                }
                            }
                            e.Handled = true;
                        }
                        break;
                    case SKTouchAction.Released:
                        {
                            TouchEntry entry;
                            bool res = TouchDictionary.TryGetValue(e.Id, out entry);
                            long elapsedms = (DateTime.Now.Ticks - entry.PressTime.Ticks) / TimeSpan.TicksPerMillisecond;
                            if (elapsedms <= GHConstants.MoveOrPressTimeThreshold && !_touchMoved)
                            {
                                if (!_showDirections && !_showNumberPad)
                                {
                                    int x = 0, y = 0, mod = 0;
                                    float canvaswidth = canvasView.CanvasSize.Width;
                                    float canvasheight = canvasView.CanvasSize.Height;
                                    float offsetX = (canvaswidth - _mapWidth) / 2;
                                    float offsetY = (canvasheight - _mapHeight) / 2;

                                    lock (ClipLock)
                                    {
                                        if (ClipX > 0 && (_mapWidth > canvaswidth || _mapHeight > canvasheight))
                                        {
                                            offsetX -= (ClipX - (GHConstants.MapCols - 1) / 2) * _tileWidth;
                                            offsetY -= (ClipY - GHConstants.MapRows / 2) * _tileHeight;
                                        }
                                    }
                                    offsetX += _mapOffsetX;
                                    offsetY += _mapOffsetY + _mapFontAscent;

                                    if (_tileWidth > 0)
                                        x = (int)((e.Location.X - offsetX) / _tileWidth);
                                    if (_tileHeight > 0)
                                        y = (int)((e.Location.Y - offsetY) / _tileHeight);

                                    if (x > 0 && x < GHConstants.MapCols && y >= 0 && y < GHConstants.MapRows)
                                    {
                                        if (MapMode == GHMapMode.Look)
                                            mod = (int)NhGetPosMods.Click2;
                                        else if (MapMode == GHMapMode.Travel)
                                            mod = (int)NhGetPosMods.Click1;
                                        else
                                            mod = (int)NhGetPosMods.Click3;

                                        ConcurrentQueue<GHResponse> queue;
                                        if (ClientGame.ResponseDictionary.TryGetValue(_clientGame, out queue))
                                        {
                                            queue.Enqueue(new GHResponse(_clientGame, GHRequestType.Location, x, y, mod));
                                        }
                                    }
                                }
                                else
                                {
                                    if(e.Location.X >= canvasButtonRect.Left && e.Location.X <= canvasButtonRect.Right && e.Location.Y >= canvasButtonRect.Top && e.Location.Y <= canvasButtonRect.Bottom)
                                    {
                                        int resp = 0;
                                        SKPoint RectLoc = new SKPoint(e.Location.X - canvasButtonRect.Left, e.Location.Y - canvasButtonRect.Top);

                                        if (RectLoc.Y < canvasButtonRect.Height * 0.3 && RectLoc.X < canvasButtonRect.Width * 0.3)
                                            resp = -7;
                                        else if (RectLoc.Y < canvasButtonRect.Height * 0.3 && RectLoc.X > canvasButtonRect.Width * 0.7)
                                            resp = -9;
                                        else if (RectLoc.Y > canvasButtonRect.Height * 0.7 && RectLoc.X < canvasButtonRect.Width * 0.3)
                                            resp = -1;
                                        else if (RectLoc.Y > canvasButtonRect.Height * 0.7 && RectLoc.X > canvasButtonRect.Width * 0.7)
                                            resp = -3;
                                        else if (RectLoc.Y < canvasButtonRect.Height * 0.3)
                                            resp = -8; //ch = "k";
                                        else if (RectLoc.Y > canvasButtonRect.Height * 0.7)
                                            resp = -2; // ch = "j";
                                        else if (RectLoc.X < canvasButtonRect.Width * 0.3)
                                            resp = -4; // ch = "h";
                                        else if (RectLoc.X > canvasButtonRect.Width * 0.7)
                                            resp = -6; // ch = "l";
                                        else
                                            resp = showNumberPad ? -5 : 46; /* '.', or self */

                                        if (showNumberPad)
                                            resp -= 10;

                                        ConcurrentQueue<GHResponse> queue;
                                        if (ClientGame.ResponseDictionary.TryGetValue(_clientGame, out queue))
                                        {
                                            queue.Enqueue(new GHResponse(_clientGame, GHRequestType.GetChar, resp));
                                        }
                                    }
                                    else if (showNumberPad && e.Location.X < canvasButtonRect.Left && e.Location.Y >= canvasButtonRect.Top && e.Location.Y <= canvasButtonRect.Top + canvasButtonRect.Height / 3)
                                    {
                                        int resp = -10;
                                        ConcurrentQueue<GHResponse> queue;
                                        if (ClientGame.ResponseDictionary.TryGetValue(_clientGame, out queue))
                                        {
                                            queue.Enqueue(new GHResponse(_clientGame, GHRequestType.GetChar, resp));
                                        }
                                    }
                                }
                            }
                            if (TouchDictionary.ContainsKey(e.Id))
                                TouchDictionary.Remove(e.Id);
                            if (TouchDictionary.Count == 0)
                                _touchMoved = false;
                            e.Handled = true;
                        }
                        break;
                    case SKTouchAction.Cancelled:
                        break;
                    case SKTouchAction.Exited:
                        break;
                    case SKTouchAction.WheelChanged:
                        break;
                    default:
                        break;
                }
            }
        }

        private static SKColor GHDarkGray = new SKColor(96, 96, 96);

        public static SKColor NHColor2SKColor(nhcolor nhcolor)
        {
            SKColor res = SKColors.White;
            switch (nhcolor)
            {
                case nhcolor.CLR_BLACK:
                    res = GHDarkGray;
                    break;
                case nhcolor.CLR_RED:
                    res = SKColors.Red;
                    break;
                case nhcolor.CLR_GREEN:
                    res = SKColors.Green;
                    break;
                case nhcolor.CLR_BROWN:
                    res = SKColors.Brown;
                    break;
                case nhcolor.CLR_BLUE:
                    res = SKColors.Blue;
                    break;
                case nhcolor.CLR_MAGENTA:
                    res = SKColors.Magenta;
                    break;
                case nhcolor.CLR_CYAN:
                    res = SKColors.Cyan;
                    break;
                case nhcolor.CLR_GRAY:
                    res = SKColors.LightGray;
                    break;
                case nhcolor.NO_COLOR:
                    break;
                case nhcolor.CLR_ORANGE:
                    res = SKColors.Orange;
                    break;
                case nhcolor.CLR_BRIGHT_GREEN:
                    res = SKColors.LightGreen;
                    break;
                case nhcolor.CLR_YELLOW:
                    res = SKColors.Yellow;
                    break;
                case nhcolor.CLR_BRIGHT_BLUE:
                    res = SKColors.LightBlue;
                    break;
                case nhcolor.CLR_BRIGHT_MAGENTA:
                    res = SKColors.LightPink;
                    break;
                case nhcolor.CLR_BRIGHT_CYAN:
                    res = SKColors.LightCyan;
                    break;
                case nhcolor.CLR_WHITE:
                    res = SKColors.White;
                    break;
                case nhcolor.CLR_MAX:
                    break;
                default:
                    break;
            }

            return res;
        }
        public static Color NHColor2Color(nhcolor color)
        {
            Color res = Color.White;
            switch (color)
            {
                case nhcolor.CLR_BLACK:
                    res = Color.DarkGray;
                    break;
                case nhcolor.CLR_RED:
                    res = Color.Red;
                    break;
                case nhcolor.CLR_GREEN:
                    res = Color.Green;
                    break;
                case nhcolor.CLR_BROWN:
                    res = Color.Brown;
                    break;
                case nhcolor.CLR_BLUE:
                    res = Color.Blue;
                    break;
                case nhcolor.CLR_MAGENTA:
                    res = Color.Magenta;
                    break;
                case nhcolor.CLR_CYAN:
                    res = Color.Cyan;
                    break;
                case nhcolor.CLR_GRAY:
                    res = Color.LightGray;
                    break;
                case nhcolor.NO_COLOR:
                    break;
                case nhcolor.CLR_ORANGE:
                    res = Color.Orange;
                    break;
                case nhcolor.CLR_BRIGHT_GREEN:
                    res = Color.LightGreen;
                    break;
                case nhcolor.CLR_YELLOW:
                    res = Color.Yellow;
                    break;
                case nhcolor.CLR_BRIGHT_BLUE:
                    res = Color.LightBlue;
                    break;
                case nhcolor.CLR_BRIGHT_MAGENTA:
                    res = Color.LightPink;
                    break;
                case nhcolor.CLR_BRIGHT_CYAN:
                    res = Color.LightCyan;
                    break;
                case nhcolor.CLR_WHITE:
                    res = Color.White;
                    break;
                case nhcolor.CLR_MAX:
                    break;
                default:
                    break;
            }

            return res;
        }
        public static Color NHColor2GrayedColor(nhcolor color)
        {
            Color basecolor = NHColor2Color(color);
            Color bgcolor = Color.Black;
            Color grayedcolor;
            if (color == nhcolor.NO_COLOR || color == nhcolor.CLR_WHITE)
                grayedcolor = new Color((basecolor.R + bgcolor.R) / 2, (basecolor.G + bgcolor.G) / 2, (basecolor.B  + bgcolor.B) / 2, basecolor.A);
            else /* Special colors are brighter */
                grayedcolor = new Color((basecolor.R * 2 + bgcolor.R) / 3, (basecolor.G * 2 + bgcolor.G) / 3, (basecolor.B * 2 + bgcolor.B) / 3, basecolor.A);

            return grayedcolor;
        }
        public void SetMapSymbol(int x, int y, int glyph, int bkglyph, int c, int color, uint special)
        {
            lock (_mapDataLock)
            {
                _mapData[x, y].Glyph = glyph;
                _mapData[x, y].BkGlyph = bkglyph;
                _mapData[x, y].Symbol = Char.ConvertFromUtf32(c);
                _mapData[x, y].Color = NHColor2SKColor((nhcolor)color);
                _mapData[x, y].Special = special;
            }
        }
        public void SetMapCursor(int x, int y)
        {
            lock (_mapDataLock)
            {
                _mapCursorX = x;
                _mapCursorY = y;
            }
        }
        public void ClearMap()
        {
            lock (_mapDataLock)
            {
                for (int x = 1; x < GHConstants.MapCols; x++)
                {
                    for (int y = 0; y < GHConstants.MapRows; y++)
                    {
                        _mapData[x, y].Glyph = UnexploredGlyph;
                        _mapData[x, y].BkGlyph = NoGlyph;
                        _mapData[x, y].Symbol = "";
                        _mapData[x, y].Color = SKColors.Black;// default(MapData);
                        _mapData[x, y].Special = 0;
                    }
                }
            }
        }


        private void PickupButton_Clicked(object sender, EventArgs e)
        {
            GenericButton_Clicked(sender, e, ',');
        }
        private void SearchButton_Clicked(object sender, EventArgs e)
        {
            GenericButton_Clicked(sender, e, 's');
        }
        private void KickButton_Clicked(object sender, EventArgs e)
        {
            GenericButton_Clicked(sender, e, 'k');
        }
        private void UpButton_Clicked(object sender, EventArgs e)
        {
            GenericButton_Clicked(sender, e, '<');
        }
        private void DownButton_Clicked(object sender, EventArgs e)
        {
            GenericButton_Clicked(sender, e, '>');
        }

        public void GenericButton_Clicked(object sender, EventArgs e, int resp)
        {
            if (!((resp >= '0' && resp <= '9') || (resp <= -1 && resp >= -19)))
                showNumberPad = false;

            if (_clientGame != null)
            {
                ConcurrentQueue<GHResponse> queue;
                if (ClientGame.ResponseDictionary.TryGetValue(_clientGame, out queue))
                {
                    queue.Enqueue(new GHResponse(_clientGame, GHRequestType.GetChar, resp));
                }
            }
        }

        private void InventoryButton_Clicked(object sender, EventArgs e)
        {
            GenericButton_Clicked(sender, e, 'i');
        }
        private void LookHereButton_Clicked(object sender, EventArgs e)
        {
            GenericButton_Clicked(sender, e, ':');
        }
        private void WaitButton_Clicked(object sender, EventArgs e)
        {
            GenericButton_Clicked(sender, e, '.');
        }
        private void FireButton_Clicked(object sender, EventArgs e)
        {
            GenericButton_Clicked(sender, e, 'f');
        }

        private async void MenuButton_Clicked(object sender, EventArgs e)
        {
            var cmdPage = new CommandPage(this);
            await App.Current.MainPage.Navigation.PushModalAsync(cmdPage);

        }

        private void ZeroButton_Clicked(object sender, EventArgs e)
        {
            if (CurrentYnResponses.Length >= 4)
                GenericButton_Clicked(sender, e, (int)CurrentYnResponses.Substring(0, 1).ToCharArray()[0]);
        }
        private void FirstButton_Clicked(object sender, EventArgs e)
        {
            if (CurrentYnResponses.Length >= 4)
                GenericButton_Clicked(sender, e, (int)CurrentYnResponses.Substring(1, 1).ToCharArray()[0]);
            else if (CurrentYnResponses.Length >= 2)
                GenericButton_Clicked(sender, e, (int)CurrentYnResponses.Substring(0, 1).ToCharArray()[0]);
        }

        private void SecondButton_Clicked(object sender, EventArgs e)
        {
            if (CurrentYnResponses.Length == 1)
                GenericButton_Clicked(sender, e, (int)CurrentYnResponses.Substring(0, 1).ToCharArray()[0]);
            else if (CurrentYnResponses.Length >= 4)
                GenericButton_Clicked(sender, e, (int)CurrentYnResponses.Substring(2, 1).ToCharArray()[0]);
            else if (CurrentYnResponses.Length >= 2)
                GenericButton_Clicked(sender, e, (int)CurrentYnResponses.Substring(1, 1).ToCharArray()[0]);
        }

        private void ThirdButton_Clicked(object sender, EventArgs e)
        {
            if (CurrentYnResponses.Length == 3)
                GenericButton_Clicked(sender, e, (int)CurrentYnResponses.Substring(2, 1).ToCharArray()[0]);
            else if (CurrentYnResponses.Length >= 4)
                GenericButton_Clicked(sender, e, (int)CurrentYnResponses.Substring(3, 1).ToCharArray()[0]);
        }

        private void FourthButton_Clicked(object sender, EventArgs e)
        {
            if (CurrentYnResponses.Length >= 5)
                GenericButton_Clicked(sender, e, (int)CurrentYnResponses.Substring(4, 1).ToCharArray()[0]);
        }

        private void RepeatButton_Clicked(object sender, EventArgs e)
        {
            GenericButton_Clicked(sender, e, GHUtils.Ctrl('A'));
        }

        private void CastButton_Clicked(object sender, EventArgs e)
        {
            GenericButton_Clicked(sender, e, 'Z');
        }

        private void LootButton_Clicked(object sender, EventArgs e)
        {
            GenericButton_Clicked(sender, e, 'l');
        }

        private void EatButton_Clicked(object sender, EventArgs e)
        {
            GenericButton_Clicked(sender, e, 'e');
        }

        private void CountButton_Clicked(object sender, EventArgs e)
        {
            GenericButton_Clicked(sender, e, 'n');
        }

        private void RunButton_Clicked(object sender, EventArgs e)
        {
            GenericButton_Clicked(sender, e, 'G');
        }

        private void ESCButton_Clicked(object sender, EventArgs e)
        {
            GenericButton_Clicked(sender, e, 27);
        }

        private void ToggleModeButton_Clicked(object sender, EventArgs e)
        {
            MapTravelMode = !MapTravelMode;
            if(MapTravelMode)
            {
                ToggleModeButton.BackgroundColor = Color.Green;
                MapMode = GHMapMode.Travel;
                MapLookMode = false;
                LookModeButton.BackgroundColor = Color.DarkBlue;
            }
            else
            {
                ToggleModeButton.BackgroundColor = Color.DarkBlue;
                MapMode = GHMapMode.Normal;
            }
        }
        private void LookModeButton_Clicked(object sender, EventArgs e)
        {
            MapLookMode = !MapLookMode;
            if(MapLookMode)
            {
                LookModeButton.BackgroundColor = Color.Green;
                MapMode = GHMapMode.Look;
                MapTravelMode = false;
                ToggleModeButton.BackgroundColor = Color.DarkBlue;
            }
            else 
            {
                LookModeButton.BackgroundColor = Color.DarkBlue;
                MapMode = GHMapMode.Normal;
            }
        }
        private void NoClipButton_Clicked(object sender, EventArgs e)
        {
            MapNoClipMode = !MapNoClipMode;
            if (MapNoClipMode)
            {
                //NoClipButton.BackgroundColor = Color.Green;
            }
            else
            {
                //NoClipButton.BackgroundColor = Color.DarkBlue;
            }

        }

        private void ChatButton_Clicked(object sender, EventArgs e)
        {
            GenericButton_Clicked(sender, e, 'C');
        }

        private void ThrowQuiveredButton_Clicked(object sender, EventArgs e)
        {
            GenericButton_Clicked(sender, e, 't');
        }

        private void ApplyWieldedButton_Clicked(object sender, EventArgs e)
        {
            GenericButton_Clicked(sender, e, 'a');
        }

        private void ZapButton_Clicked(object sender, EventArgs e)
        {
            GenericButton_Clicked(sender, e, 'z');
        }

        private void SwapWeaponButton_Clicked(object sender, EventArgs e)
        {
            GenericButton_Clicked(sender, e, 'x');
        }

        private void LootContextButton_Clicked(object sender, EventArgs e)
        {
            GenericButton_Clicked(sender, e, 'l');
        }

        private void EatContextButton_Clicked(object sender, EventArgs e)
        {
            GenericButton_Clicked(sender, e, 'e');
        }

        private void DropAllContextButton_Clicked(object sender, EventArgs e)
        {
            GenericButton_Clicked(sender, e, 'D');
        }

        private void SacrificeContextButton_Clicked(object sender, EventArgs e)
        {
            GenericButton_Clicked(sender, e, GHUtils.Meta('o'));
        }
    }

    public class ColorConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {

            if ((bool)value == true)
            {
                return Color.White;
            }

            return Color.DarkGray;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if ((bool)value == true)
            {
                return Color.White;
            }

            return Color.DarkGray;
        }
    }

    public class TouchEntry 
    {
        public SKPoint Location;
        public DateTime PressTime;

        public TouchEntry()
        {

        }
        public TouchEntry(SKPoint loc, DateTime time)
        {
            Location = loc;
            PressTime = time;
        }
    }

}