$(
	function () {
		$( "#left" ).imageScroller( {loading:'Wait please...'} );
		
		$( "#right" ).imageScroller( {speed:'4000', direction:'right'} );
		
		$( "#top" ).imageScroller( {direction:'top'} );

		$( "#bottom" ).imageScroller( {speed:'3500', direction:'bottom'} );
	}
)