jQuery(function(){
    jQuery('.animation').css('visibility','hidden');
    jQuery(window).scroll(function(){
     var windowHeight = jQuery(window).height(),
         topWindow = jQuery(window).scrollTop();
     jQuery('.animation').each(function(){
      var targetPosition = jQuery(this).offset().top;
      if(topWindow > targetPosition - windowHeight + 100){
       jQuery(this).addClass("fadeInDown");
      }
     });
    });
    });

 