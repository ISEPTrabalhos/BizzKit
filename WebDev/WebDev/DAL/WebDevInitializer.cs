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
-60 60 0
-60 -60 0
60 -60 0
60 60 0
-60 25 0
-50 25 0
-60 -25 0
-50 -25 0
-40 -50 0
-40 30 0
-40 35 0
20 35 0
-20 -60 0
-20 20 0
0 35 0
0 -30 0
10 -30 0
20 60 0
20 -10 0
45 60 0
45 50 0
45 30 0
35 -15 0
60 -20 0
50 -20 0
15 -45 0
40 -60 0
40 -50 0
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
                    name = "Background music",
                    url = "http://localhost:43492/assets/sounds/The_Simpsons.wav",
                },
                new Sounds {
                    ID = 2,
                    name = "Against the wall",
                    url = "http://localhost:43492/assets/sounds/wall.wav"
                },
                new Sounds {
                    ID = 3,
                    name = "Falling",
                    url = "http://localhost:43492/assets/sounds/falling.wav"
                }
            };

            sounds.ForEach(s => context.Sounds.Add(s));

            var textures = new List<Textures>
            {
                new Textures {
                    ID = 1,
                    name = "Floor texture",
                    url = "http://localhost:43492/assets/textures/floor.jpg"
                },
                new Textures {
                    ID = 2,
                    name = "Walls texture",
                    url = "http://localhost:43492/assets/textures/Wall.jpg"
                }
            };

            textures.ForEach(s => context.Textures.Add(s));

            context.SaveChanges();

            var enemies = new List<Enemies>
            {
                new Enemies{
                    ID=1,
                    name="Mummy",
                    url="http://localhost:43492/assets/enemies/mummy.mdl"
                },
                new Enemies{
                    ID=2,
                    name="Zombie",
                    url="http://localhost:43492/assets/enemies/SpitterL4D2v1.mdl"
                }
            };

            enemies.ForEach(s => context.Enemies.Add(s));
        }
         
        
        
    }

   
}
