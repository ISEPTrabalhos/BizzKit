using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace WebDev.Models
{
    public class User
    {
        [Key]
        public string username { get; set; }

        [Required]
        public string passwordHash { get; set; }
    }

    public class Level
    {
        [Key]
        public string name { get; set; }

        [Required]
        public string content { get; set; }
    }

    public class Score
    {
        [Key]
        [ForeignKey("User")]
        [Column(Order = 1)]
        public string username { get; set; }

        [Key]
        [ForeignKey("Level")]
        [Column(Order = 2)]
        public string levelName { get; set; }

        [Required]
        public int score { get; set; }

        public virtual User User { get; set; }

        public virtual Level Level { get; set; }
    }
}
