using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.Entity;
using WebDev.Models;

namespace WebDev.DAL
{
    public class WebDevContext : DbContext
    {
        public WebDevContext()
            : base("WebDevContext")
        {

        }

        public DbSet<User> Users { get; set; }

        public DbSet<Level> Levels { get; set; }

        public DbSet<Score> Scores { get; set; }

        public DbSet<Downloads> Downloads { get; set; }

        public DbSet<Sounds> Sounds { get; set; }

        public DbSet<Textures> Textures { get; set; }

        public DbSet<GameRoute> GameRoute { get; set; }

        public DbSet<Enemies> Enemies { get; set; }
    }
}
