jQuery(function(){

if (!jQuery("#spoiler-style").attr("is_set")) {
	jQuery("head").append(
		"<style id='spoiler-style' is_set='1'>.spoiler-no {display: none;} .spoiler-head {cursor: pointer;}</style>");
		}

jQuery('.spoiler-body').hide();

jQuery('.spoiler-head').click(function(){
	jQuery(this).toggleClass("closed").toggleClass("open").next().slideToggle();
	})

});
