#include "debug.h"

#include "ui/ui.h"

void UI_DrawArrow() 
{

}

int selected = -1;

void UI_DrawBoard(game_t *game, ImVec2 boardsize)
{
    ImVec2 cellsize = (ImVec2){boardsize.x / BOARDSIZE,
                            boardsize.y / BOARDSIZE};

	static ImGuiTableFlags flags = 
		ImGuiTableFlags_NoPadInnerX | ImGuiTableFlags_NoPadOuterX | 
        //ImGuiTableFlags_NoHostExtendY | //ImGuiTableFlags_PreciseWidths |
        ImGuiTableFlags_PreciseWidths | ImGuiTableFlags_SizingFixedFit;// |
        //ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersH;
        //ImGuiTableFlags_SizingFixedFit;// | ;
		//ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV |
		//ImGuiTableFlags_BordersH | ImGuiTableFlags_;
	igBeginTable("Board", 8, flags, boardsize, 0);

	for (size_t i = 0; i < BOARDSIZE; i++)
		igTableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, cellsize.x, i);

	igPushStyleColor_Vec4(ImGuiCol_Button, (ImVec4){0, 0, 0, 0});
	igPushStyleVar_Vec2(ImGuiStyleVar_CellPadding, (ImVec2){0,0});
	igPushStyleVar_Vec2(ImGuiStyleVar_FramePadding, (ImVec2){0,0});

    int hx = igTableGetHoveredColumn();
    int hy = igTableGetHoveredRow();

	for (size_t y = 0; y < BOARDSIZE; y++) 
    {
		igTableNextRow(ImGuiTableRowFlags_None, cellsize.y);

		for (size_t x = 0; x < BOARDSIZE; x++) 
        {
			ImU32 a;

			if ((BOARDSIZE * y + (x + y % 2)) % 2)
				a = (255 << 0) | (206 << 8) | (158 << 16) | (255 << 24);
			else
				a = (209 << 0) | (139 << 8) | (71 << 16) | (255 << 24);

            if (x == hx && y == hy)
                a = (0 << 0) | (139 << 8) | (71 << 16) | (255 << 24);

            if (selected == (BOARDSIZE * y + x))
                a = (0 << 0) | (255 << 8) | (255 << 16) | (255 << 24);


			igTableSetColumnIndex(x);
			igTableSetBgColor(ImGuiTableBgTarget_CellBg, a, x);

			int click = 0;

			if (Chess_IsOccupied(&game->state, y * BOARDSIZE + x))
            {              
				click = igImageButtonEx(
					y * BOARDSIZE + x + 1,
					(ImTextureID)UI_ImageFromPiece(GetPieceType(&game->state, y * BOARDSIZE + x), GetPieceColor(&game->state, y * BOARDSIZE + x)),
					cellsize, (ImVec2){0.0f, 0.0f}, (ImVec2){1.0f, 1.0f},
					(ImVec4){0, 0, 0, 0}, (ImVec4){255, 255, 255, 255}, 0);                        
            }else 
			{
				click = igImageButtonEx(
					y * BOARDSIZE + x + 1,
					(ImTextureID)0,
					cellsize, (ImVec2){0.0f, 0.0f}, (ImVec2){1.0f, 1.0f},
					(ImVec4){0, 0, 0, 0}, (ImVec4){255, 255, 255, 0}, 0);    
			}

			if (click)
			{
				if (selected == -1)
				{
					if (game->state.boards[OFFSET_OCCUPIED] & ((uint64_t)1 << (y * BOARDSIZE + x)))
						selected = y * BOARDSIZE + x;
				}
				else 
				{
					if (selected != y * BOARDSIZE + x)
						MovePiece(&game->state, selected, y * BOARDSIZE + x);
					
					selected = -1;
				}
			}

			//

			// igTextUnformatted(&c, &c+1);
			// igSelectable_Bool("###text_1",b, ImGuiSelectableFlags_None,
			// (ImVec2){30,30}); igSelectable_Bool("Image#image_1",b,
			// ImGuiSelectableFlags_None, (ImVec2){30,30});

			// ADD VAR SYSTEM BUT MAKE VAIRABLES POINTERS SO THEY CAN BE SET TO
			// APPLICATION VALUES
		}
	}

	igPopStyleColor(1);
	igPopStyleVar(2);
	igEndTable();
}