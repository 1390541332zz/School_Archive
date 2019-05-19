	component qsystop is
		port (
			clk_clk         : in  std_logic                    := 'X';             -- clk
			ledout_export   : out std_logic_vector(7 downto 0);                    -- export
			reset_reset_n   : in  std_logic                    := 'X';             -- reset_n
			switchin_export : in  std_logic_vector(7 downto 0) := (others => 'X'); -- export
			hex0_readdata   : out std_logic_vector(6 downto 0);                    -- readdata
			hex1_name       : out std_logic_vector(6 downto 0);                    -- name
			hex2_readdata   : out std_logic_vector(6 downto 0);                    -- readdata
			hex3_readdata   : out std_logic_vector(6 downto 0);                    -- readdata
			hex4_readdata   : out std_logic_vector(6 downto 0);                    -- readdata
			hex5_readdata   : out std_logic_vector(6 downto 0)                     -- readdata
		);
	end component qsystop;

	u0 : component qsystop
		port map (
			clk_clk         => CONNECTED_TO_clk_clk,         --      clk.clk
			ledout_export   => CONNECTED_TO_ledout_export,   --   ledout.export
			reset_reset_n   => CONNECTED_TO_reset_reset_n,   --    reset.reset_n
			switchin_export => CONNECTED_TO_switchin_export, -- switchin.export
			hex0_readdata   => CONNECTED_TO_hex0_readdata,   --     hex0.readdata
			hex1_name       => CONNECTED_TO_hex1_name,       --     hex1.name
			hex2_readdata   => CONNECTED_TO_hex2_readdata,   --     hex2.readdata
			hex3_readdata   => CONNECTED_TO_hex3_readdata,   --     hex3.readdata
			hex4_readdata   => CONNECTED_TO_hex4_readdata,   --     hex4.readdata
			hex5_readdata   => CONNECTED_TO_hex5_readdata    --     hex5.readdata
		);

