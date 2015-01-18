using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Data.Entity;
using WebDev.Models;

namespace WebDev.DAL
{
    public class WebDevInitializer : DropCreateDatabaseIfModelChanges<WebDevContext>
    {
        protected override void Seed(WebDevContext context)
        {
            var users = new List<User> {
                new User {
                    username = "test",
                    passwordHash = "098F6BCD4621D373CADE4E832627B4F6"
                }
            };

            users.ForEach(u => context.Users.Add(u));
            context.SaveChanges();

            var levels = new List<Level> {
                new Level {
                    name = "quarto1",
                    content = @"28
-60 60 5
-60 -60 5
60 -60 5
60 60 5
-60 25 5
-50 25 5
-60 -25 5
-50 -25 5
-40 -50 5
-40 30 5
-40 35 5
20 35 5
-20 -60 5
-20 20 5
0 35 5
0 -30 5
10 -30 5
20 60 5
20 -5 5
45 60 5
45 50 5
45 30 5
35 -15 5
60 -20 5
50 -20 5
15 -45 5
40 -60 5
40 -50 5
18
0 1 1 1
1 2 1 1
2 3 1 1
0 3 1 1
4 5 1 5
6 7 1 5
8 9 1 5
10 11 1 5
12 13 1 5
14 15 1 5
15 16 1 5
17 18 1 5
19 20 1 5
18 21 1 5
18 22 1 5
23 24 1 5
24 25 1 5
26 27 1 5"
                },
                new Level {
                    name = "test",
                    content = @"4
-60 60 0
-60 -60 0
60 -60 0
60 60 0
2
0 1 1 1
1 2 1 1"
                },
                new Level {
                    name = "quarto2",
                    content = @"20
-30 60 5
-30 -60 5
30 -60 5
30 60 5
-30 25 2
-25 25 2
-30 -25 2
-25 -25 2
-15 20 2
-15 40 2
-15 50 0
-15 10 0
-15 -20 2
-15 -40 2
-15 -50 0
-15 -10 0
10 -60 2
10 30 2
10 60 2
20 30 2
14
0 1 5 5
1 2 5 5
2 3 5 5
3 0 5 5
4 5 5 5
6 7 5 5
8 9 5 5
9 10 5 5
8 11 5 5
12 13 5 5
13 14 5 5
12 15 5 5
16 17 5 5
18 19 5 5
"
                },
                new Level {
                    name = "quarto3",
                    content = @"31
-60 60 5
-60 -60 5
60 -60 5
60 60 5
-60 25 2
-50 25 2
-60 -25 2
-50 -25 2
-30 40 2
-30 -15 2
-30 -25 0
-45 40 0
25 40 2
-20 -60 2
-20 -50 2
-5 -60 2
-5 -20 2
-5 -30 2
20 -30 2
25 60 2
25 -10 2
35 -20 2
45 -25 0
50 60 2
50 50 2
0 20 2
60 -40 2
45 -40 2
20 -50 2
40 -60 2
40 -50 2
21
0 1 5 5
1 2 5 5
2 3 5 5
0 3 5 5
4 5 5 5
6 7 5 5
8 9 5 5
9 10 5 5
8 11 5 5
8 12 5 5
13 14 5 5
15 16 5 5
17 18 5 5
19 20 5 5
20 21 5 5
21 22 5 5
23 24 5 5
12 25 5 5
26 27 5 5
27 28 5 5
29 30 5 5"
                },
                new Level {
                    name = "mundo1",
                    content = @"28
-60 60 5
-60 -60 5
60 -60 5
60 60 5
-60 25 5
-50 25 5
-60 -25 5
-50 -25 5
-40 -50 5
-40 30 5
-40 35 5
20 35 5
-20 -60 5
-20 20 5
0 35 5
0 -30 5
10 -30 5
20 60 5
20 -5 5
45 60 5
45 50 5
45 30 5
35 -15 5
60 -20 5
50 -20 5
15 -45 5
40 -60 5
40 -50 5
18
0 1 1 1
1 2 1 1
2 3 1 1
0 3 1 1
4 5 1 5
6 7 1 5
8 9 1 5
10 11 1 5
12 13 1 5
14 15 1 5
15 16 1 5
17 18 1 5
19 20 1 5
18 21 1 5
18 22 1 5
23 24 1 5
24 25 1 5
26 27 1 5"
                }
            };

            levels.ForEach(m => context.Levels.Add(m));
            context.SaveChanges();

            var scores = new List<Score> {
                new Score {
                    username = "test",
                    levelName = "quarto1",
                    score = 1
                }
            };

            scores.ForEach(s => context.Scores.Add(s));
            context.SaveChanges();

            var downloads = new List<Downloads>
            {
                new Downloads {
                    ID = 1,
                    fileName = "app",
                    quantity = 200
                }
            };

            downloads.ForEach(s => context.Downloads.Add(s));

            var sounds = new List<Sounds>
            {
                new Sounds {
                    ID = 1,
                    name = "Background music_background",
                    url = "wvm041.dei.isep.ipp.pt/Lapr5/assets/sounds/background.wav",
                },
                new Sounds {
                    ID = 2,
                    name = "Crashing_wall",
                    url = "wvm041.dei.isep.ipp.pt/Lapr5/assets/sounds/wall.wav"
                },
                new Sounds {
                    ID = 3,
                    name = "Falling_fall",
                    url = "wvm041.dei.isep.ipp.pt/Lapr5/assets/sounds/fall.wav"
                }
            };

            sounds.ForEach(s => context.Sounds.Add(s));

            var textures = new List<Textures>
            {
                new Textures {
                    ID = 1,
                    name = "Floor 1",
                    url = "wvm041.dei.isep.ipp.pt/Lapr5/assets/textures/floor.jpg"
                },
                new Textures {
                    ID = 2,
                    name = "Wall 1",
                    url = "wvm041.dei.isep.ipp.pt/Lapr5/assets/textures/wall1.jpg"
                },
                new Textures {
                    ID = 3,
                    name = "Floor 2",
                    url = "wvm041.dei.isep.ipp.pt/Lapr5/assets/textures/floor2.jpg"
                },
                new Textures {
                    ID = 4,
                    name = "Wall 2",
                    url = "wvm041.dei.isep.ipp.pt/Lapr5/assets/textures/wall2.jpg"
                }
            };

            textures.ForEach(s => context.Textures.Add(s));

            context.SaveChanges();

            var enemies = new List<Enemies>
            {
                new Enemies{
                    ID=1,
                    name="Mummy",
                    url="wvm041.dei.isep.ipp.pt/Lapr5/assets/enemies/mummy.mdl"
                },
                new Enemies{
                    ID=2,
                    name="Zombie",
                    url="wvm041.dei.isep.ipp.pt/Lapr5/assets/enemies/SpitterL4D2v1.mdl"
                }
            };

            enemies.ForEach(s => context.Enemies.Add(s));
        }
         
        
        
    }

   
}
