using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace WebDev.Models
{
    public class Sounds
    {
        [Key]
        public int ID { get; set; }

        [Required]
        public string name { get; set; }

        [Required]
        public string url { get; set; }
    }
}