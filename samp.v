	initial begin
		assertion_REG_result_result_ready = 1'b0 ;
		
		
		#0 assertion_REG_result_result_ready = 1'b1 ;
		assertion_REG_result = assertion_REG_result_wire;
	end

	// ----- Assertion result

	assign assertion_REG_result_wire = ( ((TTGSHADOWPKG::resolvex_legal === 1'b1) ? ( ( |( REG_wire[31:0] ) !== 1'b1 && |( REG_wire[31:0] ) !== 1'bx ) ) :  (( |( REG_wire[31:0] ) !== 1'b1 ) )) || ( (ARESETN) != 0 ) );

	always@(assertion_REG_result_wire) begin
		assertion_REG_result <= ( ( assertion_REG_result_wire === 1'b1 ) || ( assertion_REG_result_wire === 1'bz ) ) ;
	end

	// ----- Check assertion pass conditions

	always@( posedge assertion_REG_result ) begin
		if (assertion_REG_result_result_ready === 1'b1 ) begin
			$display("[RADIX] -PASS- Security property assertion_REG passes at time %0d", $time);
		end
	end

	// ----- Check assertion fail conditions

	longint assertion_REG_result_count;
	longint assertion_REG_MAX_ERROR;

	initial begin
		assertion_REG_result_count = 0 ;
		if (!$value$plusargs("TTG_MAX_AST_ERROR_COUNT=%d", assertion_REG_MAX_ERROR)) begin
			$display("[RADIX] Maximum security property error count not set for security property <assertion_REG>. Running until finish.");
			assertion_REG_MAX_ERROR = 0 ;
		end else if ( assertion_REG_MAX_ERROR <= 0 ) begin
			$display("[RADIX] Maximum security property error count set to non-positive integer (%0d) for security property <assertion_REG>. Running until finish.", assertion_REG_MAX_ERROR);
		end else begin
			$display("[RADIX] Maximum security property error count set to: (%0d) for security property <assertion_REG>.", assertion_REG_MAX_ERROR);
		end
	end

	always@( negedge assertion_REG_result ) begin
		if (assertion_REG_result_result_ready === 1'b1 ) begin
			if ( assertion_REG_result == 1'b0 ) begin
				assertion_REG_result_count += 1 ;
				$display("[RADIX] -FAIL- Security property assertion_REG failed at time %0d", $time);
				$display("[RADIX] - Occurred (%0d) time(s).", assertion_REG_result_count);

				if ( ( assertion_REG_MAX_ERROR > 0 ) && ( assertion_REG_result_count >= assertion_REG_MAX_ERROR) ) begin
					$finish;
				end
			end
		end
	end

	// ----- Monitor for assertion tracking

	logic assertion_REG_is_tracking ;

	always_comb begin
		assertion_REG_is_tracking = (|( REG_tnt )) ;
	end

	always@( assertion_REG_is_tracking ) begin
		if ( assertion_REG_is_tracking === 1'b1 ) begin
			$display("[RADIX] Security property assertion_REG is tagging information flow from assertion sources at time (%0d).", $time);
		end
		else if ( assertion_REG_is_tracking === 1'bx ) begin
			$display("[RADIX] Security Property assertion_REG is tagging information flow (assertion conditions resolve to x) from assertion sources at time (%0d).", $time);
		end
		else begin
			$display("[RADIX] Assertion assertion_REG has stopped tagging information flow from assertion sources at time (%0d).", $time);
		end
	end

	final begin
		$display("[RADIX] Total failures for security property <assertion_REG>: (%0d)", assertion_REG_result_count );
	end
